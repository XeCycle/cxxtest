template <class T>
auto f(T) -> decltype(g(T()));

int g(int);

#ifdef HAS_F_DEFINITION_IN_THIS_TU
// clang accepts this file if this is defined, rejects otherwise;
// gcc rejects in both cases
template <class T>
auto f(T) -> decltype(g(T())) { return g(T()); }
#endif

int main()
{
  return f(0);
}
