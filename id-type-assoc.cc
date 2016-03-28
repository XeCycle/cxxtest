#include <cstdint>

template <uint32_t id, class... entries>
struct realm : entries... {};

template <int32_t id, class ContentType>
struct type_entry {};

using test_realm = realm<42, type_entry<1, int>, type_entry<2, double>, type_entry<3, int> >;

template <class t, int32_t id>
constexpr int32_t lookup_id(type_entry<id, t>)
{
  return id;
}

int main()
{
  return lookup_id<int>(test_realm());
}
