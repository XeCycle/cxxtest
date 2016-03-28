#include <functional>

struct foo {
  int operator()()
  {}
};

int main(int argc, char *argv[])
{
  return std::is_function<foo()>::value;
}
