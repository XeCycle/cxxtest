#include <type_traits>

struct fail_type {};

template <class T>
struct success_type {
  using type = T;
};

template <class Struct, class R, class Arg>
success_type<Arg>
deduce_unary_mem_arg_type(R(Struct::*)(Arg));

struct test {

  void operator()(int);
  void operator()();

};

int main()
{

  static_assert(std::is_same<
                  decltype(deduce_unary_mem_arg_type(&test::operator()))::type,
                  int
                >::value, "");

  return 0;
}
