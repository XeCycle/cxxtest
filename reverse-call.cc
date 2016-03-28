#include <cassert>
#include <utility>

template <class...>
struct type_sequence {};

namespace fn_impl {
// call fn with arguments in reverse

template <class RestSequence, class ReversedSequence>
struct reverse_call_t;

template <class... Reversed>
struct reverse_call_t<type_sequence<>, type_sequence<Reversed...>> {
  template <class Function>
  static constexpr auto call(Function&& f, Reversed... args)
    -> decltype(f(std::forward<Reversed>(args)...))
  {
    return f(std::forward<Reversed>(args)...);
  }
};

template <class First, class... Rest, class... Reversed>
struct reverse_call_t<type_sequence<First, Rest...>, type_sequence<Reversed...>> {
  template <class Function>
  static constexpr auto call(Function&& f,
                             First&& first, Rest&&... rest, Reversed&&... reversed)
    -> decltype(
      reverse_call_t<type_sequence<Rest...>, type_sequence<First, Reversed...>>::call(
        std::forward<Function>(f), std::declval<Rest>()...,
        std::declval<First>(), std::declval<Reversed>()...))
  // above works, but the following decltype expression, which is an exact
  // copy of what is inside the function body, fails in GCC.  Both works in
  // clang.
  // 
  // -> decltype(reverse_call_t<type_sequence<Rest...>, type_sequence<First, Reversed...>>::call(
  //               std::forward<Function>(f), std::forward<Rest>(rest)...,
  //               std::forward<First>(first), std::forward<Reversed>(reversed)...))
  {
    return reverse_call_t<type_sequence<Rest...>, type_sequence<First, Reversed...>>::call(
      std::forward<Function>(f), std::forward<Rest>(rest)...,
      std::forward<First>(first), std::forward<Reversed>(reversed)...);
  }
};

} // namespace fn_impl

template <class Function, class... T>
constexpr auto reverse_call(Function&& f, T&&... args)
  -> decltype(
    fn_impl::reverse_call_t<type_sequence<T...>, type_sequence<>>::call(
      std::forward<Function>(f), std::forward<T>(args)...))
{
  return fn_impl::reverse_call_t<type_sequence<T...>, type_sequence<>>::call(
    std::forward<Function>(f), std::forward<T>(args)...);
}

int main()
{

  assert(reverse_call([](int x, int y) { return x-y; }, 1, 2) == 1);

  return 0;
}
