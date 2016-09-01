#include "vfunction.hh"

int b(function<int()>&& f)
{
  return f();
}
