const float* find_lt(const float* first, const float* last, float threshold)
{
  if (last-first < 8)
    return std::find_if(first, last, [=](float v) { return v < threshold; });

  __m256 vthreshold = _mm256_set1_ps(threshold);
  for (; first < last-8; first+=8) {
    auto cmp = _mm256_cmp_ps(_mm256_loadu_ps(first), vthreshold, _CMP_LT_OQ);
    if (_mm256_testz_ps(cmp, cmp))
      continue;
    return first + tzcnt(_mm256_movemask_ps(cmp));
  }

  {
    // at end; it does not hurt to compare some more
    auto cmp = _mm256_cmp_ps(_mm256_loadu_ps(last-8), vthreshold, _CMP_LT_OQ);
    if (!_mm256_testz_ps(cmp, cmp))
      return last-8 + tzcnt(_mm256_movemask_ps(cmp));
  }

  return last;
}
