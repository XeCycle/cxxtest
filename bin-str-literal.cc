#include <cstddef>
#include <cassert>
#include <string>

template <size_t N>
std::string bin_string(const char (&str)[N])
{
  return { str, str+N-1 };
}

std::string operator"" _bin(const char* str, size_t size)
{
  return { str, str+size };
}

int main()
{

  auto s = bin_string("foo\0bar");
  assert(s.size() == 7);

  auto s2 = "foo\0bar"_bin;
  assert(s2.size() == 7);

  return 0;
}
