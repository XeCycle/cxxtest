struct A {
  int a;
};

template <class Struct, class Member>
struct holder {
  Member Struct::* memptr;
};

template <class Struct, class Member>
constexpr auto try_hold(Member Struct::* ptr) -> holder<Struct, Member>
{
  return { ptr };
}

int main(int argc, char *argv[])
{

  constexpr auto h = try_hold(&A::a);

  return 0;
}
