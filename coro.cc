#include <cstdio>
#include <cstdlib>
#include <experimental/coroutine>
#include <variant>

namespace stdcoro = std::experimental;

template <class T>
struct async_task;

template <class T>
struct async_promise__base_returning {
  void return_value(T&&) {}
};

template <>
struct async_promise__base_returning<void> {
  void return_void() {}
};

template <class T>
struct async_promise : async_promise__base_returning<T> {

  async_task<T> get_return_object();

  constexpr stdcoro::suspend_always initial_suspend()
  {
    return {};
  }

  constexpr stdcoro::suspend_never final_suspend()
  {
    return {};
  }

  void unhandled_exception()
  {
    abort();
  }

};

template <class T>
struct async_task {
  using promise_type = async_promise<T>;

  friend struct async_promise<T>;

private:

  using handle_type = stdcoro::coroutine_handle<promise_type>;

  handle_type h;

  explicit async_task(handle_type h_)
    : h(h_)
  {}

public:

  friend void start(async_task task)
  {
    task.h.resume();
  }

};

template <class T>
async_task<T> async_promise<T>::get_return_object()
{
  return async_task<T>(
    stdcoro::coroutine_handle<async_promise>
    ::from_promise(*this));
}

template <class T>
struct async_value;

template <class T>
struct async_value_producer {

private:

  struct empty_t {};
  using state_t = std::variant<
    empty_t,
    T,
    stdcoro::coroutine_handle<>>;
  enum {
    empty,
    resolved,
    awaiting
  };
  state_t state;

  friend struct async_value<T>;

public:

  async_value_producer() = default;

  async_value_producer(async_value_producer const&) = delete;
  async_value_producer& operator=(async_value_producer const&) = delete;
  async_value_producer(async_value_producer&&) = delete;
  async_value_producer& operator=(async_value_producer&&) = delete;

  async_value<T> value();

  template <class... Arg>
  void emplace_value(Arg&&... arg)
  {
    stdcoro::coroutine_handle<> coro;
    switch (state.index()) {
    case awaiting:
      coro = std::move(std::get<awaiting>(state));
      // fallthrough
    case empty:
      state.template emplace<resolved>((Arg&&)arg...);
      break;
    case resolved:
      return;
    }
    if (coro)
      coro.resume();
  }

};

template <class T>
struct async_value {

private:

  using P = async_value_producer<T>;

  friend P;

  typename P::state_t* p_state;

  explicit async_value(typename P::state_t& st)
    : p_state(&st)
  {}

public:

  friend auto operator co_await(async_value av)
  {
    struct waiter {
      typename P::state_t* p_state;

      bool await_ready()
      {
        return p_state->index() == P::resolved;
      }

      bool await_suspend(stdcoro::coroutine_handle<> h)
      {
        switch (p_state->index()) {
        case P::empty:
          p_state->template emplace<P::awaiting>(h);
          return true;
        case P::resolved:
          return false;
        default:
          abort();
        }
      }

      T await_resume()
      {
        return (T&&)std::get<P::resolved>(*p_state);
      }

    };
    return waiter { av.p_state };
  }

};

template <class T>
async_value<T> async_value_producer<T>::value()
{
  return async_value<T>(state);
}

async_task<void>
f(async_value<int> val)
{
  auto x = co_await val;
  printf("%d\n", x);
}

int main()
{
  async_value_producer<int> p;
  start(f(p.value()));
  puts("started");
  p.emplace_value(42);
  puts("sent");
}
