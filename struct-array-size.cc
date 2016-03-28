struct S { int x; };

int main()
{

  static_assert((long long)(void*)(((S*)0)+1) == 4, "right");

  return 0;
}
