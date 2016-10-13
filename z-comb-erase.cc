#include <functional>

template <class F>
struct Z_t {

    F f;

    template <class... X>
    constexpr auto operator()(X&&... x) &
        -> decltype(f(*this, (X&&)x...))
    {
        return f(*this, (X&&)x...);
    }

    template <class... X>
    constexpr auto operator()(X&&... x) const&
        -> decltype(f(*this, (X&&)x...))
    {
        return f(*this, (X&&)x...);
    }

};

template <class F>
Z_t<typename std::decay<F>::type>
constexpr Z(F&& f)
{
    return { (F&&)f };
}

int main()
{

  std::function<void()> f;

  (Z([&](auto self) -> void { f = self; }))();

  return 0;
}
