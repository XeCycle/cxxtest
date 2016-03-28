#include <string>

bool test(const std::string& s)
{
  return (s == "foo");
}

int main(int argc, char *argv[])
{

  return test("tetet");

  return 0;
}
