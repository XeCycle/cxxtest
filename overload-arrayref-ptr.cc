#include <cassert>
#include <cstddef>

template <size_t N>
int f(const char(&)[N])
{
  return N;
}

int f(const char*)
{
  return -1;
}

int main()
{

  assert(f("abc") == -1);

  return 0;
}
