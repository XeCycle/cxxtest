#include <iostream>
#include <functional>

struct T {
  void f();
};

int main()
{

  T t;

  auto bindf = std::bind(&T::f, &t);
  auto captf = [&t] { return t.f(); };

  std::cout << sizeof bindf << ' ' << sizeof captf << '\n';

  return 0;
}
