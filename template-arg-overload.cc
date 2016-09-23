template <int N>
int f()
{
  return 42;
}

template <unsigned N>
int f()
{
  return -42;
}

int g(int)
{
  return 42;
}

int g(unsigned)
{
  return -42;
}

int main(int argc, char** argv)
{
  return g(1) + g(1u) + f<1>() + f<1u>();
}
