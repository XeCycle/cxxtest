#include <cstddef>
#include <vector>
#include <numeric>

#include <cassert>

int main()
{

  std::vector<double> a(100000), b(100000);

  for (size_t isamp=0; isamp<1000; ++isamp)
    assert(inner_product(a.begin(), a.end(), b.begin(), double(0)) == double(0));

  return 0;
}
