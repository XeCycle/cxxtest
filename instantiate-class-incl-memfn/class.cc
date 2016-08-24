#include "class.hh"

template <bool x>
int T<x>::foo()
{
  return x;
}

template struct T<true>;
template struct T<false>;
