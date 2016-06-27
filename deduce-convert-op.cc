template <class F>
struct foo {

  template <class Ret, class... Arg>
  using fnptr = Ret(*)(Arg...);

  template <class Ret, class... Arg>
  operator fnptr<Ret, Arg...>()
  {
    return 0;
  }

};

template <class F>
foo<F> wrap(F) { return {}; }

void f(void(*)(int, char))
{}

int main(int argc, char** argv)
{
  f(wrap([](int) { return 1; }));
  return 0;
}
