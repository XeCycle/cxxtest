constexpr size_t AVX_ALIGN_MASK = sizeof(__m256) - 1;

template <class T>
T* align_up(T* p)
{
  auto n = reinterpret_cast<uintptr_t>(p);
  auto a = (n+AVX_ALIGN_MASK) & ~AVX_ALIGN_MASK;
  return reinterpret_cast<T*>(a);
}

__m256 loadu2_ps(const float* addr)
{
  return _mm256_insertf128_ps(
    _mm256_castps128_ps256(_mm_loadu_ps(addr)),
    _mm_loadu_ps(addr+4), 1);
}

const float* find_lt(const float* first, const float* last, float threshold)
{
  if (last-first < 8)
    return std::find_if(first, last, [=](float v) { return v < threshold; });

  __m256 vthreshold = _mm256_set1_ps(threshold);

  {
    // unaligned at beginning
    auto cmp = _mm256_cmp_ps(loadu2_ps(first), vthreshold, _CMP_LT_OQ);
    if (!_mm256_testz_ps(cmp, cmp))
      return first + tzcnt(_mm256_movemask_ps(cmp));
    first = align_up(first);
  }

  // aligned in the middle
  for (; first < last-8; first+=8) {
    auto cmp = _mm256_cmp_ps(_mm256_load_ps(first), vthreshold, _CMP_LT_OQ);
    if (_mm256_testz_ps(cmp, cmp))
      continue;
    return first + tzcnt(_mm256_movemask_ps(cmp));
  }

  {
    // unaligned at end
    auto cmp = _mm256_cmp_ps(loadu2_ps(last-8), vthreshold, _CMP_LT_OQ);
    if (!_mm256_testz_ps(cmp, cmp))
      return last-8 + tzcnt(_mm256_movemask_ps(cmp));
  }

  return last;
}
