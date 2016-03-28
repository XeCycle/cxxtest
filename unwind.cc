#include <iostream>

struct foo {
  ~foo()
  {
    std::cerr << "unwound\n";
  }
};

int main()
{

  try {
    foo a;
    throw 1;
  } catch(...) {
    throw;
  }

  return 0;
}
