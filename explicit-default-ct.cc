struct A {
  explicit A() = default;
};

void f(A) {}

void f(int) {}

int main(int argc, char *argv[])
{
  f({});
  return 0;
}
