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

struct fallback {};
struct preferred : fallback {};

int g_impl(fallback, const char*)
{
  return -1;
}

template <size_t N>
int g_impl(preferred, const char(&)[N])
{
  return N;
}

template <class T>
int g(T&& x)
{
  return g_impl(preferred(), (T&&)x);
}

int main()
{

  assert(f("abc") == -1);

  assert(g("abc") == 4);
  const char* str = "abc";
  assert(g(str) == -1);

  return 0;
}
