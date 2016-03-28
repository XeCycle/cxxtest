#include <iostream>

void print_once()
{
  using std::cout;
  static void* any = (cout<<"print\n", nullptr);
}

int main(int argc, char *argv[])
{
  for (int i=0; i<10; ++i)
    print_once();
  return 0;
}
