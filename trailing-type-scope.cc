template <class T>
auto f(T v) -> decltype(g(v));

int g(int) { return 0; }

template <class T>
auto f(T v) -> decltype(g(v))
{
  return g(v) + 1;
}

int main()
{
  return f(0);
}
