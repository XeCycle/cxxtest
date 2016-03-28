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

  D d {};

  d.a = 1;
  d.b = 2;
  d.c = 3;
  d.d = 4;

  static_cast<C&>(d).c = 42;

  return d.c;
}
