#include <new>
#include <iostream>

struct dtor_throw {
  ~dtor_throw() noexcept(false)
  {
    throw 1;
  }
};

int main()
{

  try {
    dtor_throw a;
  } catch (int) {
    std::cout << "stack dtor throw catched\n";
  }

  auto p = new dtor_throw;
  try {
    delete p;
  } catch (int) {
    std::cout << "delete expr throw catched\n";
  }

  auto p2 = new dtor_throw;
  try {
    operator delete(p2);
  } catch (int) {
    std::cout << "operator delete throw catched\n";
  }

  return 0;
}
