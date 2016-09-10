#include <cstddef>
#include <x86intrin.h>

__attribute__((optimize("unroll-loops")))
const float* find_min_pos(const float* first, const float* last)
{
  auto incr = _mm256_set1_epi32(8);
  auto idx = _mm256_setr_epi32(0, 1, 2, 3, 4, 5, 6, 7);
  auto min = _mm256_load_ps(first);
  auto minidx = idx;
  for (auto addr = first + 8;
       addr < last;
       addr += 8, idx = _mm256_add_epi32(idx, incr)) {
    auto v = _mm256_load_ps(addr);
    min = _mm256_min_ps(min, v);
    auto cmp = _mm256_cmp_ps(v, min, _CMP_LT_OQ);
    minidx = _mm256_blendv_epi8(minidx, idx, _mm256_castps_si256(cmp));
  }

  {
    // 0v1, 2v3 in each lane
    auto vshifted1 = _mm256_permute_ps(min, 0b01011111);
    auto ishifted1 = _mm256_shuffle_epi32(minidx, 0b01011111);
    auto cmp_0v1_2v3 = _mm256_cmp_ps(vshifted1, min, _CMP_LT_OQ);
    min = _mm256_min_ps(min, vshifted1);
    minidx = _mm256_blendv_epi8(minidx, ishifted1,
                                _mm256_castps_si256(cmp_0v1_2v3));
    // 0v2 in each lane
    auto vshifted2 = _mm256_permute_ps(min, 0b10101010);
    auto ishifted2 = _mm256_shuffle_epi32(minidx, 0b10101010);
    auto cmp_0v2 = _mm256_cmp_ps(vshifted2, min, _CMP_LT_OQ);
    min = _mm256_min_ps(min, vshifted2);
    minidx = _mm256_blendv_epi8(minidx, ishifted2,
                                _mm256_castps_si256(cmp_0v2));
    // compare high and low part
    auto vhigh = _mm256_unpackhi_ps(min, min);
    auto ihigh = _mm256_unpackhi_epi32(minidx, minidx);
    auto cmp_hl = _mm256_cmp_ps(vhigh, min, _CMP_LT_OQ);
    // no need to store min now
    minidx = _mm256_blendv_epi8(minidx, ihigh, _mm256_castps_si256(cmp_hl));
    return first + _mm256_extract_epi32(minidx, 0);
  }
}

const float* find_min_pos_scalar(const float* first, const float* last)
{
  ptrdiff_t pos = 0;
  for (ptrdiff_t i=1; i < last-first; ++i)
    pos = first[i] < first[pos] ? i : pos;
  return first + pos;
}
