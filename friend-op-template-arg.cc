#include <type_traits>

struct T {

  template <class U=T, class=typename std::enable_if<std::is_same<T, U>::value>::type>
  friend constexpr int operator+(T, T)
  {
    return 42;
  }

};

template <class T, class...>
T operator+(T, T);

int main()
{

  static_assert(T()+T() == 42, "");
  static_assert(operator+(T(), T()) == 42, "");
  static_assert(operator+<int, void>(T(), T()) == 42, "");

  return 0;
}
