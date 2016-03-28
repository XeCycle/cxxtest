#include <random>
#include <type_traits>

#include <iostream>

namespace {

std::random_device rd;
std::mt19937 gen {rd()};

template <class Int>
typename std::enable_if<std::is_integral<Int>::value, Int>::type
rand_num() {
  static std::uniform_int_distribution<Int> dist;
  return dist(gen);
}

template <class Real>
typename std::enable_if<std::is_floating_point<Real>::value, Real>::type
rand_num() {
  static std::uniform_real_distribution<Real> dist;
  return dist(gen);
}

} // end unnamed namespace

int main()
{

  using std::cout;

  cout << rand_num<short>() << " " << rand_num<float>() << "\n";

  return 0;
}
