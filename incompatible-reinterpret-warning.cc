struct compat {
  void* x;
};

struct incompat {
  int a, b;
};

int main()
{

  compat c;
  incompat i;

  (void) reinterpret_cast<void*&>(c); // good
  (void) reinterpret_cast<void*&>(i); // warn

  return 0;
}
