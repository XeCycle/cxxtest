#include <vector>
#include <algorithm>
#include <iterator>
#include <cstdint>

// Y = aX+b

__attribute__((noinline))
auto reserving(const std::vector<uint16_t>& X, float a, float b)
{
  std::vector<float> Y;
  Y.reserve(X.size());
  transform(
    X.begin(), X.end(),
    back_inserter(Y),
    [=](uint16_t x) { return a*x + b; });
  return Y;
}

__attribute__((noinline))
auto resizing(const std::vector<uint16_t>& X, float a, float b)
{
  std::vector<float> Y;
  Y.resize(X.size());
  transform(
    X.begin(), X.end(),
    Y.begin(),
    [=](uint16_t x) { return a*x + b; });
  return Y;
}

int main()
{

  std::vector<uint16_t> X(512);
  iota(X.begin(), X.end(), 0);

  return ! (reserving(X, 2.3, 4.5) == resizing(X, 2.3, 4.5));
}
