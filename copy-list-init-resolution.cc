struct T {

  explicit T() = default;

  template <class... Arg>
  T(Arg&&...) {}

};

int main()
{
  T x {};
  T y = {};
  return 0;
}
