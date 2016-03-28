#include <tuple>

template <class... A, class... B>
bool f(std::tuple<A...> a, std::tuple<B...> b)
{
  return true;
}

int main(int argc, char *argv[])
{

  (void) f<int, int>(std::make_tuple(1, 2), std::make_tuple(4, 5));

  return 0;
}
