namespace lib {

struct foo {};

inline
namespace abiv1 {

void f(foo)
{}

} // namespace abiv1

} // namespace lib

int main()
{

  f(lib::foo());

  return 0;
}
