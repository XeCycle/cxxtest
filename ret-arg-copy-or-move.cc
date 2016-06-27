struct test {
  int a;
  test() = default;
  test(const test&) : a(1) {}
  test(test&&) : a(2) {}
};

test f(test x)
{
  return x;
}

int main()
{
  return f(test{}).a;
}
