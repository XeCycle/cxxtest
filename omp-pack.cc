#include <iostream>

#include <omp.h>

template <class Action>
void run_one(Action&& action)
{
  #pragma omp task shared(action)
  action();
}

template <class... T>
void noop(T&&...)
{}

template <class... Action>
void run_all(Action&&... action)
{
  #pragma omp parallel
  #pragma omp single
  {
    noop((run_one(action), 0)...);
  }
}

int main(int argc, char *argv[])
{

  run_all([]{ std::cout << omp_get_thread_num() << '\n'; },
          []{ std::cout << omp_get_thread_num() << '\n'; });

  return 0;
}
