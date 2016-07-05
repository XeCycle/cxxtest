#include <cstddef>
#include <cassert>
#include <string>

template <size_t N>
std::string bin_string(const char (&str)[N])
{
  return { str, str+N-1 };
}

int main()
{

  auto s = bin_string("foo\0bar");
  assert(s.size() == 7);

  return 0;
}
