template <class> struct A;
template <class> struct B;

template <class Provider>
struct A : Provider {
  int operator()()
  {
    return 1 + this->template get_sibling<B>()();
  }
};

template <class Provider>
struct B : Provider {
  int x;
  int operator()() const
  {
    return x;
  }
};

struct provider_base {
protected:
  template <template <class> class Child>
  Child<provider_base>& get_sibling() &
  {
    return *static_cast<Child<provider_base>*>(this);
  }
};

template <template <class> class... Child>
struct collected : Child<provider_base>... {
private:
  struct store_t : Child<provider_base>... {};
  store_t store;
public:
  template <template <class> class C>
  C<provider_base>& get() &
  {
    return static_cast<C<provider_base>&>(store);
  }
};

int main()
{

  collected<A, B> pack{};

  return pack.get<A>()();
}
