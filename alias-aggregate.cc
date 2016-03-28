struct foo {
  char* s;
};

int main()
{
  foo f;
  char** ptr = reinterpret_cast<char**>(&f);
  (void)ptr;
  return 0;
}
