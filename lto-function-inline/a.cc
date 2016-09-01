#include <functional>

int b(std::function<int()>);

int a()
{
  return b([] { return 42; });
}
