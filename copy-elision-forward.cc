struct T {

  T() = default;
  T(T const&) { throw 1; }
  T(T&&) { throw 1; }

};

template <class T>
struct A {
  T x;
};

struct in_place_t {};

template <class T>
struct B {
  T x;

  template <class... Arg>
  explicit B(in_place_t, Arg&&... arg)
    : x((Arg&&)arg...)
  {}

};

int main()
{
  A<T> a { T() };
  try {
    B<T> b { in_place_t(), T() };
  } catch(int) {
    return 0;
  }
  return 1;
}
