#include <vector>

struct B;

struct A { std::vector<B> b; };
struct B { std::vector<A> a; };

int main()
{
  
  return 0;
}
