#include <functional>
#include <iostream>

int main()
{
  std::cout << sizeof(std::function<void()>) << '\n';
  return 0;
}
