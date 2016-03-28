#include <cstddef>
#include <utility>
#include <vector>
#include <iostream>

template <size_t prio>
struct priority_tag : priority_tag<prio-1> {};

template <>
struct priority_tag<0> {};

template <class Container, class T>
auto emplace_or_push_back_impl(Container&& cont, const T& value, priority_tag<0>)
  -> decltype(cont.push_back(value), void())
{
  std::cout << "push\n";
  cont.push_back(value);
}

template <class Container, class T>
auto emplace_or_push_back_impl(Container&& cont, const T& value, priority_tag<1>)
  -> decltype(cont.emplace_back(value), void())
{
  std::cout << "emplace\n";
  cont.emplace_back(value);
}

template <class Container, class T>
void emplace_or_push_back(Container&& cont, T&& value)
{
  return emplace_or_push_back_impl(
    std::forward<Container>(cont), std::forward<T>(value),
    priority_tag<1>());
}

template <class T>
class vector_no_emplace : public std::vector<T> {
  template <class... Arg>
  void emplace_back(Arg...) = delete;
};

int main(int argc, char *argv[])
{

  std::vector<int> a;

  emplace_or_push_back(a, 3);

  vector_no_emplace<int> b;

  emplace_or_push_back(b, 4);

  return 0;
}
