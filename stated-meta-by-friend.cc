#include <type_traits>

struct state_false {};
struct state_true : state_false {};

struct initial_state {
  friend
  std::false_type f(state_false);
};

template <class Tag>
struct enable_state {
  friend
  std::true_type f(state_true);
};

int main(int argc, char *argv[])
{

  static_assert(!decltype(f(state_true()))::value, "false");
  enable_state<int> a;
  static_assert(decltype(f(state_true()))::value, "true");

  return 0;
}
