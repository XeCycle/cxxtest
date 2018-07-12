#include <cstdio>
#include <memory>

struct use_allocator_t {
  explicit use_allocator_t() = default;
};

template <class A>
void* operator new(size_t size, use_allocator_t, A a)
{
  using traits = std::allocator_traits<A>;
  return traits::allocate(a, size);
}

template <class A>
void* operator new[](size_t size, use_allocator_t, A a)
{
  using traits = std::allocator_traits<A>;
  return traits::allocate(a, size);
}

template <class A>
void operator delete(void* p, use_allocator_t, A a)
{
  using traits = std::allocator_traits<A>;
  return traits::deallocate(a, p);
}

template <class A>
void operator delete[](void* p, use_allocator_t, A a)
{
  using traits = std::allocator_traits<A>;
  return traits::deallocate(a, static_cast<typename traits::pointer>(p), 0);
}

template <class T>
struct barfing_allocator {

  using value_type = T;

  T* allocate(size_t size)
  {
    printf("allocate %lu\n", size);
    return static_cast<T*>(::operator new(size));
  }

  void deallocate(T* p, size_t)
  {
    printf("deallocate\n");
    return ::operator delete(p);
  }

};

struct fail_halfway {
  static size_t counter;
  size_t idx;
  fail_halfway()
    : idx(++counter)
  {
    printf("I am %lu\n", idx);
    if (idx == 5)
      throw 42;
  }
  ~fail_halfway()
  {
    printf("%lu dying\n", idx);
  }
};

size_t fail_halfway::counter = 0;

int main()
{

  barfing_allocator<fail_halfway> a;

  try {
    new (use_allocator_t(), a) fail_halfway[10];
  } catch(int) {
    return 0;
  }

  return 1;
}
