struct T {
  struct M {};
  friend long f(M);
};

long x = f(T::M());

long f(T::M)
{
  return 42;
}
