#include <iostream>

#include <pthread.h>

struct T {
  T()
  {
    std::cout << "T ctor, " << pthread_self() << '\n';
  }
};

T thread_local x;
T thread_local y;

extern "C"
void f() {
  (void)&x;
}
