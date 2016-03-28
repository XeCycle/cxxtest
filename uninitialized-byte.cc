#include <cstdint>
#include <cstddef>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <memory>

union uninitialized_byte {

private:

  struct empty_t {};
  empty_t empty;

public:

  char ch;

  constexpr uninitialized_byte()
    : empty()
  {}

  constexpr uninitialized_byte(char c)
    : ch(c)
  {}

};

static_assert(sizeof(uninitialized_byte) == 1, "unexpected layout");

template <class Vector>
void write_to_buffer(Vector& buf, const char* str, size_t count)
{
  auto old_size = buf.size();
  buf.resize(old_size + count);
  std::copy(str, str+count, reinterpret_cast<char*>(std::addressof(buf[old_size])));
}

template <class F, class... Arg>
__attribute__((optimize("no-inline")))
uint64_t time(F&& f, Arg&&... arg)
{
  using clock = std::chrono::high_resolution_clock;
  using std::operator"" ns;

  auto start = clock::now();
  ((F&&)f)((Arg&&)arg...);
  return (clock::now() - start)/1ns;

}

int main()
{

  const size_t N = 50000000;
  
  for (size_t isample=0; isample<10; ++isample) {

    std::vector<uninitialized_byte> buf;
    buf.reserve(N*sizeof(float));

    std::cout << "noinit: " << time([&](){
      for (size_t i=0; i<N; ++i) {
        float x = 123;
        write_to_buffer(buf, reinterpret_cast<const char*>(&x), sizeof(float));
      }
    }) << '\n';

    std::vector<char> buf_char;
    buf_char.reserve(N*sizeof(float));

    std::cout << "char: " << time([&](){
      for (size_t i=0; i<N; ++i) {
        float x = 123;
        write_to_buffer(buf_char, reinterpret_cast<const char*>(&x), sizeof(float));
      }
    }) << '\n';

  }

  return 0;
}
