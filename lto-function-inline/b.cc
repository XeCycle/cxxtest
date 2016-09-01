#include <functional>

int b(std::function<int()> f)
{
  return f();
}
