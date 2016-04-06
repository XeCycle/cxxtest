#include <cstdint>
#include <cstddef>
#include <vector>
#include <chrono>
#include <iostream>

const size_t NSAMPLES = 10000;
const size_t ROWS = 4000;
const size_t COLS = 512;

int main()
{

  using clock = std::chrono::high_resolution_clock;

  auto start = clock::now();

  for (size_t isamp=0; isamp<NSAMPLES; ++isamp) {
    std::vector<std::vector<uint16_t> > mat(ROWS);
    for (auto& vec : mat)
      vec.reserve(COLS);
  }

  std::chrono::duration<int64_t, std::nano> dur = clock::now() - start;

  std::cout << dur.count()/NSAMPLES << '\n';

  return 0;
}
