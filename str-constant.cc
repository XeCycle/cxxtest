#include <cstddef>
#include <type_traits>
#include <utility>

#include <iostream>

template <char... x>
using string_constant = std::integer_sequence<char, x...>;

template <char, class>
struct prepend
{};

template <char head, char... rest>
struct prepend<head, string_constant<rest...> > {
  using type = string_constant<head, rest...>;
};

template <const char* s, size_t i, bool end=(s[i]==0)>
struct string_literal_to_string_constant_iterate {
  using type = typename prepend<
    s[i],
    typename string_literal_to_string_constant_iterate<s, (i+1)>::type
  >::type;
};

template <const char* s, size_t i>
struct string_literal_to_string_constant_iterate<s, i, true> {
  using type = string_constant<>;
};

template <const char* s>
struct string_literal_to_string_constant
  : string_literal_to_string_constant_iterate<s, 0>
{};

template <char... ch>
struct W {
  static void write(std::ostream& out)
  {
    using noop = int[];
    (void) noop { (out.put(ch), 0)... };
  }
};

template <class str>
struct writer_sc {};

template <char... ch>
struct writer_sc<string_constant<ch...> >
  : W<ch...>
{};

template <const char* s>
struct writer
  : writer_sc<typename string_literal_to_string_constant<s>::type>
{};

constexpr char str[] = "hello\n";

int main(int argc, char *argv[])
{

  writer<str>::write(std::cout);

  return 0;
}
