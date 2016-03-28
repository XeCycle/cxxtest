struct Foo {

  constexpr int foo() const&
  {
    return 1;
  }

  constexpr int foo() &&
  {
    return 2;
  }

};

int main(int argc, char *argv[])
{
  return Foo().foo();
}
