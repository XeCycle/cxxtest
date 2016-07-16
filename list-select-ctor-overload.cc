#include <cassert>

struct foo {
  template <class Arg>
  foo(Arg&&...) {}
};

int f(foo)
{
  return 1;
}

int f(int)
{
  return 2;
}

int main()
{

  assert(f({"a", "b", "c"}) == 1);
  assert(f(1) == 2);

  return 0;
}
