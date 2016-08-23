struct T {
  char a;
  int : 0;
  char b;
};

int main()
{
  return sizeof(T);
}
