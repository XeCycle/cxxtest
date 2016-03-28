void f() {}
int g() { return 0; }

int main(int argc, char *argv[])
{
  return g(f());
}
