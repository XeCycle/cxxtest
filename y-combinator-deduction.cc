#include <functional>

void f(std::function<void()>);

template <class F>
struct Y_t {

    F f;

    template <class... X>
    auto operator()(X&&... x) const&
        -> decltype(f(*this, (X&&)x...))
    {
        return f(*this, (X&&)x...);
    }

    template <class... X>
    auto operator()(X&&... x) &
        -> decltype(f(*this, (X&&)x...))
    {
        return f(*this, (X&&)x...);
    }

    template <class... X>
    auto operator()(X&&... x) &&
        -> decltype(std::move(f)(std::move(*this), (X&&)x...))
    {
        return std::move(f)(*this, (X&&)x...);
    }

};

template <class F>
Y_t<typename std::decay<F>::type>
Y(F&& f)
{
    return { (F&&)f };
}

void g()
{
  int x;
  auto fetch_loop = [](auto action, auto end) {
    return [=, action=std::move(action), end=std::move(end)](int n) mutable {
      f([=, action=std::move(action), end=std::move(end)]() mutable {
          // it only compiles with that trailing return type uncommented
          Y([action, end](auto&& next, int n) mutable /*-> void*/ {
              if (n & 1) {
                f([=, n=std::move(n), next=(decltype(next)&&)next]() mutable {
                  next(n + 1);
                });
              } else if (n > 0) {
                action(n, (decltype(next)&&)next);
              } else {
                end();
              }
            })(n);
        });
    };
  };

  fetch_loop([](int n, auto&& next) { (void)(decltype(next)&&)(n); },
             [] {});
}
