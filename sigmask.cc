#include <iostream>

#include <unistd.h>
#include <signal.h>

struct scope_sigmask_t {

  sigset_t saved_sigset;

  scope_sigmask_t(const scope_sigmask_t&) = delete;
  scope_sigmask_t(scope_sigmask_t&&) = delete;

  scope_sigmask_t()
  {
    sigset_t set;
    sigfillset(&set);
    sigemptyset(&saved_sigset);
    sigprocmask(SIG_SETMASK, &set, &saved_sigset);
  }

  ~scope_sigmask_t()
  {
    sigprocmask(SIG_SETMASK, &saved_sigset, 0);
  }

};

int main()
{

  std::cout << "masked sleep\n"; flush(std::cout);
  {
    scope_sigmask_t mask;
    sleep(5);
  }

  std::cout << "normal sleep\n"; flush(std::cout);
  sleep(5);

  return 0;
}
