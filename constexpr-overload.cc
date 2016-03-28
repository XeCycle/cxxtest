template <int n>
struct fixed_holder {
  static const int value = n;
};

struct runtime_holder {
  int value;
};

// constexpr auto try_hold(const int n) -> fixed_holder<n>
// {
//   return {};
// }

template <class... T>
constexpr runtime_holder try_hold(int n, T...)
{
  return { n };
}

int main(int argc, char *argv[])
{

  auto ptr = new int;

  auto x = try_hold(*ptr);

  return 0;
}
