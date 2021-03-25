#include <cstddef>
#include <cstdlib>
#include <random>
#include <algorithm>

const float* find_min_pos(const float* first, const float* last);
const float* find_min_pos_sse(const float* first, const float* last);
const float* find_min_pos_scalar(const float* first, const float* last);

int main()
{

  constexpr size_t s16mb = (16<<20);

  constexpr size_t s = s16mb / sizeof(float);

  std::random_device randdev;
  std::mt19937 gen(randdev());
  std::uniform_real_distribution<float> dist(0, 10);

  float* arr = (float*)aligned_alloc(32, s16mb);

  for (size_t i=0; i<40; ++i)
  {
    std::generate(arr, arr+s, [&] { return dist(gen); });
    // auto pvector = find_min_pos(arr, arr+s);
    auto psse = find_min_pos_sse(arr, arr+s);
    auto pscalar = find_min_pos_scalar(arr, arr+s);
    if (*pscalar != *psse)
      abort();
  }

  return 0;
}
