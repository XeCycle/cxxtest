#include <cstdio>

void f(const char* a, const char* b)
{
  printf("%p %p\n", a, b);
}

template <class A, class B>
void g(A&& a, B&& b)
{
  f((A&&)a, static_cast<B&&>(b));
}

int main()
{

  g("abcdefg", "abcdefg");

  return 0;
}
