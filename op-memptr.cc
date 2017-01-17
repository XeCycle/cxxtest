#include <tuple>
#include <type_traits>

template <class Int, Int n>
struct IC : std::integral_constant<Int, n>
{};

template <size_t n>
using SC = IC<size_t, n>;

using std::get;

template <class Tup, class Int, Int n>
constexpr auto operator->*(Tup&& t, IC<Int, n>)
  -> decltype(get<static_cast<size_t>(n)>((Tup&&)t))
{
  return get<static_cast<size_t>(n)>((Tup&&)t);
}

int main()
{

  constexpr auto t = std::make_tuple(1, 2.3, "4");

  static_assert(t->*SC<1>() == 2.3, "");

  return 0;
}
