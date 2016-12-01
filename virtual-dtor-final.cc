struct A {
  virtual ~A() = default;
};

struct B : A {
  virtual ~B() final = default;
};

struct C : B {
};

int main()
{
  C c;
  return 0;
}
