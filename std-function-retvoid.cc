#include <functional>

int main(int argc, char** argv)
{

  std::function<void(int)> f = [](int) { return true; };

  f(0);

  return 0;
}
