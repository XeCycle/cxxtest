#include <cstddef>
#include <x86intrin.h>

const float* find_min_pos_sse(const float* first, const float* last)
{
  union {
    __m128 m;
    float f[4];
  } min { _mm_loadu_ps(first) };
  union {
    __m128i m;
    int i[4];
  } minidx { _mm_setzero_si128() };
  for (int32_t i=4; i < last-first; i+=4) {
    auto idxbase = _mm_set1_epi32(i);
    auto v = _mm_loadu_ps(first+i);
    auto cmp = _mm_cmplt_ps(v, min.m);
    min.m = _mm_min_ps(min.m, v);
    minidx.m = _mm_blendv_epi8(minidx.m, idxbase, _mm_castps_si128(cmp));
  }
  auto offsets = _mm_setr_epi32(0, 1, 2, 3);
  minidx.m = _mm_add_epi32(minidx.m, offsets);

  size_t mini = 0;
  if (min.f[1] < min.f[mini]) mini = 1;
  if (min.f[2] < min.f[mini]) mini = 2;
  if (min.f[3] < min.f[mini]) mini = 3;
  return first + minidx.i[mini];
}

#if 0

const float* find_min_pos(const float* first, const float* last)
{
  auto min = _mm256_load_ps(first);
  auto minidx = _mm256_setzero_si256();
  for (int32_t i=8; i < last-first; i+=8) {
    auto idxbase = _mm256_set1_epi32(i);
    auto v = _mm256_load_ps(first+i);
    auto cmp = _mm256_cmp_ps(v, min, _CMP_LT_OQ);
    min = _mm256_min_ps(min, v);
    minidx = _mm256_blendv_epi8(minidx, idxbase, _mm256_castps_si256(cmp));
  }

  auto offsets = _mm256_setr_epi32(0, 1, 2, 3, 4, 5, 6, 7);
  minidx = _mm256_add_epi32(minidx, offsets);

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
    auto vhigh = _mm256_permute2f128_ps(min, min, 0b10000101);
    auto ihigh = _mm256_permute2f128_si256(minidx, minidx, 0b10000101);
    auto cmp_hl = _mm256_cmp_ps(vhigh, min, _CMP_LT_OQ);
    // no need to store min now
    minidx = _mm256_blendv_epi8(minidx, ihigh, _mm256_castps_si256(cmp_hl));
    return first + _mm256_extract_epi32(minidx, 0);
  }
}

#endif

const float* find_min_pos_scalar(const float* first, const float* last)
{
  ptrdiff_t pos = 0;
  for (ptrdiff_t i=1; i < last-first; ++i)
    pos = first[i] < first[pos] ? i : pos;
  return first + pos;
}
