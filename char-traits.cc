#include <string>
#include <iostream>

int main(int argc, char *argv[])
{
  std::cout << std::char_traits<char>::eof() << '\n';
  return 0;
}
