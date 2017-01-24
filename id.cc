#include <type_traits>
#include <utility>

void f() {}

template <class X>
X id(X&& x)
{
  return (X&&)x;
}

// using fn = void();

// fn g() { return f; }

#define ASSERT_TYPE(expr, typ) \
  static_assert(std::is_same<decltype(expr), typ>::value, "")

int main()
{

  using fn_rref = void(&&)();

  auto&& _f = id((fn_rref)f);
  ASSERT_TYPE(_f, void(&)());
  (void)_f;

  // // so wtf is it on array prvalue...?
  // using _ = int[];
  // auto&& x = id(_{1, 2, 3});
  // ASSERT_TYPE(x, int(&)[3]);
  // (void)x;

  return 0;
}
