unsigned long roundup(unsigned long n)
{
    auto lzcnt = __builtin_clzl(n);
    return 1<<(64-lzcnt);
}

int main()
{
  return roundup(5);
}
