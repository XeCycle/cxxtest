int main()
{

  auto f = [&f](int n) {
    if (n==0)
      return 1;
    return n * f(n-1);
  };

  return f(4);
}
