#include <cstddef>

struct S {
  bool a;
  int x;
  double b;
};

int main()
{

  static_assert(offsetof(S, a) == 0, "a good");
  static_assert(offsetof(S, x) == 4, "x good");
  static_assert(offsetof(S, b) == 8, "b good");

  return 0;
}
