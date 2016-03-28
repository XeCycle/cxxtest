#include <type_traits>

struct x {};

template <class T>
typename std::enable_if<std::is_same<T, x>::value, int>::type
f();

template <class T>
auto g(const T&) -> decltype(f<T>());

template <class T>
typename std::enable_if<std::is_same<T, char>::value, int>::type
f() { return 1; }

template <class T>
auto g(const T&) -> decltype(f<T>()) { return f<T>(); }

namespace adl {
struct z {};
template <class T>
typename std::enable_if<std::is_same<T, z>::value, int>::type
f() { return 2; }
}

int main() { g(adl::z()); }
