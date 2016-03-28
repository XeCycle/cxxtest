#include <iostream>

// template <class T, size_t N>
// struct array_length {
//   static const size_t value = N;
// };

template <class T, size_t N>
constexpr size_t array_length(T(&)[N]) {
  return N;
}

int main(int argc, char** argv)
{
  char a[10];
  std::cout << array_length(a) << std::endl;
}
