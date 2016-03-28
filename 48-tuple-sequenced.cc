#include <tuple>
#include <iostream>

int main(int argc, char *argv[])
{

  using std::get;
  using std::cout;

  int x[] = {1, 2};

  int* i = x;

  auto t = std::tuple<int, int>{*i++, *i++};

  cout << get<0>(t) << get<1>(t) << "\n";

  return 0;
}
