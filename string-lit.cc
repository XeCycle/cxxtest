#include <cstddef>

struct holder {

  const char* data;

  constexpr char operator[](size_t n) const
  {
    return data[n];
  }

};

int main(int argc, char *argv[])
{

  static_assert((holder{"abc"})[1]=='b', "");

  return 0;
}
