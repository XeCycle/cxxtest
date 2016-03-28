struct inner {};

struct outer {
  inner x;
};

int f(const inner&) { return 1; }
int f(inner&&) { return 2; }

int main()
{
  outer&& z = {};
  return f(((outer&&)z).x);
}
