#include <type_traits>
#include <utility>

template <class>
struct check_callable_t;

template <class Ret, class... Arg>
struct check_callable_t<Ret(Arg...)> {

  struct fallback {};
  struct preferred : fallback {};

  template <class F>
  constexpr static auto check_impl(F&& f, preferred)
    -> decltype(static_cast<Ret>(((F&&)f)(std::declval<Arg>()...)), std::true_type())
  {
    return {};
  }

  template <class F>
  constexpr static std::false_type check_impl(F&&, fallback)
  {
    return {};
  }

  template <class F>
  constexpr static auto check(F&& f)
  {
    return check_callable_t::check_impl((F&&)f, preferred());
  }

};

template <class Signature, class F>
constexpr auto check_callable(F&& f)
{
  return check_callable_t<Signature>::check((F&&)f);
}

auto result = check_callable<void()>([](auto&&...) {});

static_assert(decltype(result)::value, "");
