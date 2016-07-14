#include <string>
#include <iostream>

template <char... digit>
struct literal {
  constexpr operator std::string() const
  {
    return { digit... };
  }
};

template <char... digit>
literal<digit...>
operator"" _bigint()
{
  return {};
}

int main()
{

  auto n = 999999999999999999999999999999999999999999999999999_bigint;
  std::cout << std::string(n) << '\n';

  return 0;
}
