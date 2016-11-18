#include <iostream>
#include <thread>
#include <atomic>

#include <unistd.h>
#include <pthread.h>
#include <dlfcn.h>

int main()
{

  using fn_t = void(*)();

  std::atomic<fn_t> f;

  std::cout << "main, " << pthread_self() << '\n';

  std::thread t([&f] {
      std::cout << "thread, " << pthread_self() << '\n';
      sleep(2);
      f();
    });

  sleep(1);

  auto lib = dlopen("dlopen-tls-test.so", RTLD_NOW);

  auto resolved_f = reinterpret_cast<fn_t>(dlsym(lib, "f"));
  std::cout << "main before use\n";
  resolved_f();
  f = resolved_f;

  t.join();

  return 0;
}
