namespace lib {
// pull in namespace lib for ADL so that it can find later defined functions
struct lib_ns_tag {};

// f name a concept more strict than g
int f(int, lib_ns_tag) { return 0; }

// so all types implemented f gets g automatically
template <class T>
auto g(T v, lib_ns_tag) -> decltype(f(v, lib_ns_tag{}))
{
  return f(v, lib_ns_tag{});
}

// for all types with a .m member supported by f
template <class T>
auto f(T o, lib_ns_tag) -> decltype(f(o.m, lib_ns_tag{}))
{
  return f(o.m, lib_ns_tag{});
}
}

namespace app {
template <class T>
struct Foo { T m; };
}

int main()
{
  using lib::g;
  return g(app::Foo<int>{}, lib::lib_ns_tag{});
}
