#include <functional>

template <class IntA, class IntB>
constexpr IntA max2(IntA a, IntB b)
{
  return a>b ? a : b;
}

template <class Int>
constexpr Int max(Int x)
{
  return x;
}

template <class Int, class... Rest>
constexpr Int max(Int first, Rest... rest)
{
  return max2(first, max(rest...));
}

template <class... T>
struct common_holder {
  alignas(alignof(T)...) char common_memory[max(sizeof(T)...)];
};

struct vu_vtable_base {
  std::function<void(char*)> destruct;
};

template <class VTable, class... T>
struct virtual_union {

  typedef common_holder<T...> holder_type;

  const VTable* const vtptr;
  holder_type holder;
  
};
