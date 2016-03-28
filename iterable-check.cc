#include <iostream>

#define check_iterable(container)                               \
  (([&]() -> void { for (auto&& x : container) (void)x; })())

template <class Container>
auto print(Container&& cont) -> decltype(check_iterable(cont))
{
  for (auto&& x : cont)
    std::cout << x;
}

int main()
{
  int a[] = { 1, 2, 3 };
  print(x);
}
