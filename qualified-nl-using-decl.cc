#include <iterator>

namespace foo {

using std::begin;

}

int main(int argc, char *argv[])
{

  int x[3];
  foo::begin(x);

  return 0;
}
