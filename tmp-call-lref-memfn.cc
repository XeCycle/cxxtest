struct F {
  void operator()() &
  {}
};

int main()
{
  F()();
  return 0;
}
