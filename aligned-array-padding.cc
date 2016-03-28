#include <cstdint>

struct alignas(32) four { int x; };
struct alignas(64) eight { int x; };

int main()
{

  static_assert(sizeof(four) == sizeof(eight), "size match");
  static_assert((uintptr_t)(void*)(((four*)0)+1) == (uintptr_t)(void*)(((eight*)0)+1),
                "array padding match");

  return 0;
}
