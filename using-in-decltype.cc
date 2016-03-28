#include <iterator>

template <class Iterable>
auto foo(Iterable&& it) -> decltype(begin(it), std::true_type())
{
  using std::begin;
  return {};
}

int main(int argc, char *argv[])
{
  int a[1];
  return foo(a);
}
