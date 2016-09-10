#include <cstddef>
#include <cstdlib>
#include <numeric>

const float* find_min_pos(const float* first, const float* last);
const float* find_min_pos_scalar(const float* first, const float* last);

int main()
{

  constexpr size_t s16mb = (16<<20);

  constexpr size_t s = s16mb / sizeof(float);

  float* arr = (float*)aligned_alloc(32, s16mb);

  for (size_t i=0; i<1000; ++i)
  {
    auto pvector = find_min_pos(arr, arr+s);
    auto pscalar = find_min_pos_scalar(arr, arr+s);
    if (pscalar != pvector)
      abort();
  }

  return 0;
}
