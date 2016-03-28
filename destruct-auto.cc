int main(int argc, char *argv[])
{

  auto x = 0;

  x.~(decltype(x))();

  return 0;
}
