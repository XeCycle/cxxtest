#include <cstdio>

extern "C"
void a();

extern "C"
void b()
{
  try {
    a();
  } catch(int) {
    printf("caught\n");
  }
}
