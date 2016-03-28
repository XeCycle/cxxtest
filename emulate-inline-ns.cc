namespace lib {

namespace abiv1 {

struct foo {};

void do_foo(foo)
{
}

} // namespace abiv1

using namespace abiv1;

} // namespace lib

int main(int argc, char *argv[])
{

  lib::foo a;
  do_foo(a);

  return 0;
}
