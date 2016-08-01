#include "inline-odr-decl.hh"

template <class X>
int T::f()
{
  return sizeof(X);
}
