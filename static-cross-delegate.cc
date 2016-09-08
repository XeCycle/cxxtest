#include <iostream>

template <class> struct A;
template <class> struct B;

template <class Provider>
struct A {
  int operator()()
  {
    return 1 + static_cast<Provider*>(this)->template get_sibling<B>()();
  }
};

template <class Provider>
struct B {
  int x;
  int operator()() const
  {
    return x;
  }
};

template <template <class> class... Child>
struct collected {
private:
  struct store_t : Child<store_t>... {
    template <template <class> class C>
    C<store_t>& get_sibling() &
    {
      return *static_cast<C<store_t>*>(this);
    }
  };
  store_t store;
public:
  template <template <class> class C>
  C<store_t>& get() &
  {
    return static_cast<C<store_t>&>(store);
  }
};

int main()
{

  collected<A, B> pack{};

  static_assert(sizeof pack == sizeof(int), "EBO craziness");

  return pack.get<A>()();
}
