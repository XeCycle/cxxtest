#include "vfunction.hh"

int b(function<int()>&&);

int a()
{
  return b([] { return 42; });
}
