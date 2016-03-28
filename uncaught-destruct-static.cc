#include <iostream>

struct print_on_destruct {
  ~print_on_destruct()
  {
    std::cout << "destructed\n";
  }
};

void fn()
{
  static print_on_destruct a;
  (void)a;
}

int main()
{

  try {
    print_on_destruct stack_var;
    fn();
    throw 1;
  } catch(...) {
    return 1;
  }

  return 0;
}
