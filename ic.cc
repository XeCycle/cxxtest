#include <type_traits>
#include <cstddef>
#include <cstdint>

#include <tuple>
#include <utility>

template <class Int, Int v>
struct integral_constant : std::integral_constant<Int, v> {
  // backport from C++14
  constexpr Int operator()() const
  {
    return v;
  }
};

template <char x>
using char_constant = integral_constant<char, x>;

template <size_t x>
using index_constant = integral_constant<size_t, x>;

template <bool x>
using bool_constant = integral_constant<bool, x>;

// utilities on extended integral_literal

template <class Tuple, class Int, Int index>
constexpr auto operator()(Tuple&& tuple, integral_constant<Int, index>)
  -> decltype(std::get<index>(std::forward<Tuple>(tuple)))
{
  return std::get<index>(std::forward<Tuple>(tuple));
}

template <class Int, Int base, size_t exp>
struct static_pow
  : integral_constant<Int, base * static_pow<Int, base, exp-1>()>
{};

template <class Int, Int base>
struct static_pow<Int, base, 0>
  : integral_constant<Int, 1>
{};

template <char ch, class=void>
struct digit_from_char : integral_constant<char, ch-'0'> {
  static_assert('0'<=ch && ch<='9', "non-digit given");
};

template <char ch>
struct digit_from_char<ch, typename std::enable_if<('A'<=ch && ch<='F')>::type>
  : integral_constant<char, ch-'A'+10>
{};

template <char ch>
struct digit_from_char<ch, typename std::enable_if<('a'<=ch && ch<='f')>::type>
  : integral_constant<char, ch-'a'+10>
{};

template <class Int, Int base, Int... digits>
struct number_from_digits;

template <class Int, Int base, Int v>
struct number_from_digits<Int, base, v> {
  static constexpr Int value = v;
};

template <class Int, Int base, Int first, Int... rest>
struct number_from_digits<Int, base, first, rest...> {
  static constexpr Int value =
    first*static_pow<Int, base, sizeof...(rest)>::value
    + number_from_digits<Int, base, rest...>::value;
};

template <class Int, char... ch>
struct number_from_chars
  : number_from_digits<Int, 10, Int(digit_from_char<ch>::value)...>
{};

template <class Int>
struct number_from_chars<Int, '0'>
  : integral_constant<Int, 0>
{};

template <class Int, char... ch>
struct number_from_chars<Int, '0', ch...>
  : number_from_digits<Int, 8, Int(digit_from_char<ch>::value)...>
{};

template <class Int, char... ch>
struct number_from_chars<Int, '0', 'x', ch...>
  : number_from_digits<Int, 16, Int(digit_from_char<ch>::value)...>
{};

template <class Int, char... ch>
struct number_from_chars<Int, '0', 'X', ch...>
  : number_from_digits<Int, 16, Int(digit_from_char<ch>::value)...>
{};

template <char... ch>
integral_constant<uintmax_t, number_from_chars<uintmax_t, ch...>::value>
constexpr operator""_ic()
{
  return {};
}

int main(int argc, char *argv[])
{

  static_assert(123_ic==123, "dec");
  static_assert(0123_ic==0123, "oct");
  static_assert(0x123abc_ic==0x123abc, "hex lower");
  static_assert(0X123ABC_ic==0X123ABC, "hex upper");

  static_assert(std::make_tuple(1, 2, 3)(1_ic) == 2, "get tuple");
  static_assert(std::make_pair(1, 2)(0_ic) == 1, "get pair");

  return 0;
}
