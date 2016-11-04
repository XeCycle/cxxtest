#include "tpl.hh"

extern "C"
bool f(int const* p)
{
  return (p == &tplc<T>::value) && (*p == tplc<T>::value);
}
