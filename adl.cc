#include <type_traits>

namespace lib {

template <class T>
struct tag {};

template <class T>
auto fn() -> decltype(fn_impl(tag<T>()))
{
  return fn_impl(tag<T>());
}

} // namespace lib

namespace adl {

struct foo {};

foo fn_impl(lib::tag<foo>)
{
  return {};
}

} // namespace adl

int main(int argc, char *argv[])
{

  using lib::fn;

  auto x = fn<adl::foo>();

  return 0;
}
