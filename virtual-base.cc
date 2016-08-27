#include <iostream>

struct A {
  int a;
};

struct B : virtual A {
  int b;
};

struct C : virtual A {
  int c;
};

struct D : B, C {
  int d;
};

int main()
{

  union {
    D d;
    char mem[sizeof(D)];
  } u {};

  u.d.b = 1;
  u.d.c = 2;
  u.d.d = 3;

  u.d.a = 255;

  hex(std::cout);

  for (char byte : u.mem)
    std::cout << (unsigned short)(unsigned char)byte << ' ';
  std::cout << '\n';

  return 0;
}
