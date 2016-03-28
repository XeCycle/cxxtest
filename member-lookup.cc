struct A { int x; };
struct B { int x; };
struct C : A, B {};

int main(int argc, char** argv)
{
  C c;
  c.C::A::x = 1;
  c.B::x = 2;
}
