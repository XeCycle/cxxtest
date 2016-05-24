#include <cstdint>

constexpr bool is_little_endian()
{
  union {
    uint16_t b;
    uint8_t a;
  } u = { 1 };
  return u.a == 1;
}

int main()
{
  constexpr bool is_le = is_little_endian();
  return !is_le;
}
