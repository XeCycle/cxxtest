#include <type_traits>

template <class T>
auto f(T v) -> decltype(g(v));

int g(int) { return 0; }

template <class T>
auto f(T v) -> decltype(g(v))
{
  return g(v)+1;
}

int main()
{
  return std::is_same<decltype(f(0)), int>::value;
}
