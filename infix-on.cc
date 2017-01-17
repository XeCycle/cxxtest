#include <type_traits>
#include <functional>

// (f `on` m) a b = f (m a) (m b)

template <class F, class M>
struct on_exec_t {
  F f;
  M m;

  template <class A, class B>
  constexpr auto operator()(A&& a, B&& b) &
    -> decltype(f(m((A&&)a), m((B&&)b)))
  {
    return f(m((A&&)a), m((B&&)b));
  }

  template <class A, class B>
  constexpr auto operator()(A&& a, B&& b) const&
    -> decltype(f(m((A&&)a), m((B&&)b)))
  {
    return f(m((A&&)a), m((B&&)b));
  }

  template <class A, class B>
  constexpr auto operator()(A&& a, B&& b) &&
    -> decltype(((F&&)f)(((M&&)m)((A&&)a), ((M&&)m)((B&&)b)))
  {
    return ((F&&)f)(((M&&)m)((A&&)a), ((M&&)m)((B&&)b));
  }

  template <class A, class B>
  constexpr auto operator()(A&& a, B&& b) const&&
    -> decltype(((F const&&)f)(((M const&&)m)((A&&)a), ((M const&&)m)((B&&)b)))
  {
    return ((F const&&)f)(((M const&&)m)((A&&)a), ((M const&&)m)((B&&)b));
  }

};

template <class M>
struct on_partial_t {
  M m;

  template <class F>
  on_exec_t<typename std::decay<F>::type, M>
  constexpr operator()(F&& f) const&
  {
    return { (F&&)f, m };
  }

  template <class F>
  on_exec_t<typename std::decay<F>::type, M>
  constexpr operator()(F&& f) &&
  {
    return { (F&&)f, (M&&) m };
  }

};

template <class M>
on_partial_t<typename std::decay<M>::type>
constexpr on(M&& m)
{
  return { (M&&)m };
}

// x & f = f x
template <class F, class X>
constexpr auto operator&(X&& x, F&& f)
  -> decltype(((F&&)f)((X&&)x))
{
  return ((F&&)f)((X&&)x);
}

// extract a member by .*

template <class Mem>
struct extract_t {
  Mem m;

  template <class X>
  constexpr auto operator()(X&& x) const
    -> decltype(((X&&)x).*m)
  {
    return ((X&&)x).*m;
  }
};

template <class Mem>
extract_t<typename std::decay<Mem>::type>
constexpr extract(Mem&& m)
{
  return { (Mem&&)m };
}

int main()
{

  struct T { int x; };

  constexpr auto comp = std::less<int>() & on(extract(&T::x));

  static_assert(comp(T{1}, T{2}), "1 < 2");

  return 0;
}
