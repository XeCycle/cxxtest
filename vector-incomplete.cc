#include <vector>

struct myself {
  int a;
  std::vector<myself> children;
};

int main(int argc, char *argv[])
{
  myself x { 3, { {4}, {5} } };
  return 0;
}
