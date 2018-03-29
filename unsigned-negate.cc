#include <cstdint>
#include <cstdio>

int main()
{

  uint8_t a = 3;
  uintmax_t b = 42;

  double da = -a;
  double db = -b;

  printf("%lf %lf\n", da, db);

  return 0;
}
