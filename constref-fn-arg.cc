#include <cstdint>
#include <iostream>

struct stated_function {
  int x;
  stated_function()
    : x(0)
  {}

  void operator()()
  {
    ++x;
  }
};

template <class Function>
Function repeat(std::size_t n, Function fn)
{
  for (std::size_t i=0; i<n; ++i)
    fn();
  return fn;
}

int main()
{
  using std::cout;

  auto last = repeat(5, stated_function());
  cout << last.x << "\n";

  return 0;
}
