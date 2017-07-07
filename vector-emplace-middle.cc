#include <cstdio>
#include <vector>

struct W {

  W() = default;
  W(int) { printf("tagged ct %p\n", this); }
  W(W const& o) { printf("copy ct %p -> %p\n", &o, this); }
  W& operator=(W const& o) { printf("copy as %p -> %p\n", &o, this); return *this; }
  W(W&& o) noexcept { printf("move ct %p -> %p\n", &o, this); }
  W& operator=(W&& o) noexcept { printf("move as %p -> %p\n", &o, this); return *this; }
  ~W() { printf("dt %p\n", this); }

};

int main()
{
  std::vector<W> a;
  a.reserve(6);
  a.resize(5);
  puts("insert");
  a.emplace(a.begin() + 2, 0);
  puts("inserted");
}
