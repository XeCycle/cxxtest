#include <iostream>

struct M {
  M() = default;
  M(M const&) { std::cout << "copied\n"; }
  M(M&&) { std::cout << "moved\n"; }
};

struct T {
  M m;
  T() = default;
  T(T const&) = default;
};

int main()
{

  T a;
  T b(a);

  return 0;
}
