#include <algorithm>
#include <functional>

void test(bool max) {
  auto f = max ?
    (const int&(*)(const int&, const int&))std::max<int> :
    (const int&(*)(const int&, const int&))std::min<int>;
}
