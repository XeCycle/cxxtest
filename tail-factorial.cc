#include <cstdio>

double factorial_acc(unsigned n, double prod)
{
  if (n)
    return factorial_acc(n-1, prod*n);
  return prod;
}

double factorial(unsigned n)
{
  return factorial_acc(n, 1);
}

int main()
{
  printf("%e\n", factorial(50000000));
  return 0;
}
