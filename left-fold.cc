#include <utility>
#include <functional>

template <class BinOp, class... Arg>
struct left_fold_t;

template <class BinOp, class Arg>
struct left_fold_t<BinOp, Arg> {
  constexpr static Arg call(BinOp f, Arg a)
  {
    return a;
  }
};

template <class BinOp, class First, class Second, class... Rest>
struct left_fold_t<BinOp, First, Second, Rest...> {
  constexpr static auto call(BinOp f, First fs, Second sc, Rest... rest)
  {
    return left_fold_t<BinOp, decltype(f(fs, sc)), Rest...>::call(
      f,
      f(std::forward<First>(fs), std::forward<Second>(sc)),
      std::forward<Rest>(rest)...);
  }
};

template <class BinOp, class... Arg>
constexpr auto left_fold(BinOp f, Arg... arg)
  -> decltype(left_fold_t<BinOp, Arg...>::call(f, arg...))
{
  return left_fold_t<BinOp, Arg...>::call(f, std::forward<Arg>(arg)...);
}

int main(int argc, char *argv[])
{
  return left_fold(std::plus<int>(), 1, 2, 3);
}
