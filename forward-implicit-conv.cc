#include <type_traits>
#include <iostream>

int f(const int&)
{
  return 1;
}

int f(int&&)
{
  return 2;
}

int f(const double&)
{
  return 3;
}

int f(double&&)
{
  return 4;
}

// have this g equivalent to the h below?
template <class U>
std::enable_if_t<std::is_convertible<std::decay_t<U>, int>::value, int>
g(U&& x)
{
  using target_type = std::conditional_t<std::is_same<std::decay_t<U>, int>::value, U&&, int&&>;
  return f(static_cast<target_type>(x));
}

int h(const int& x)
{
  return f(x);
}

int h(int&& x)
{
  return f((int&&)x);
}

int main()
{

  int lint = 1;
  double ldouble = 3;

  // all are 2, but I want the first to be 1
  std::cout
    << h(lint) << '\n'
    << h(2) << '\n'
    << h(ldouble) << '\n'
    << h(4.0) << '\n'
    << '\n'
    << g(lint) << '\n'
    << g(2) << '\n'
    << g(ldouble) << '\n'
    << g(4.0) << '\n';

  return 0;
}
