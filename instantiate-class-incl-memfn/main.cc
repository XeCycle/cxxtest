#include <cassert>

#include "class.hh"

int main()
{

  T<true> a;
  T<false> b;

  assert(a.foo() == 1);
  assert(b.foo() == 0);

  return 0;
}
