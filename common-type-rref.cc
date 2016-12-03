#include <type_traits>
#include <string>
#include <cassert>

template <class A, class B>
auto f(A&& a, B&& b)
  -> decltype(true ? (A&&)a : (B&&)b)
{
  return false ? (A&&)a : (B&&)b;
}

int main()
{

  static_assert(std::is_same<decltype(f(std::string("abc"), "def")), std::string>::value, "");
  assert(f(std::string("abc"), "def") == "def");

  return 0;
}
