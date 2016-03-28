#include <type_traits>

int main(int argc, char *argv[])
{

  static_assert(std::is_same<char, signed char>::value, "char is signed");

  return 0;
}
