#include <cstddef>
#include <string>
#include <memory>
#include <type_traits>

#include <vector>
#include <iostream>
#include <cassert>

template <class Char, class Traits=std::char_traits<Char>,
          class Alloc=std::allocator<Char> >
class basic_c_string {
public:
  static_assert(std::is_empty<Alloc>::value,
                "C-aliasable string cannot hold stateful allocators");

  using traits_type = Traits;
  using value_type = Char;
  using allocator_type = Alloc;
  using size_type = typename std::allocator_traits<Alloc>::size_type;
  using difference_type = typename std::allocator_traits<Alloc>::difference_type;
  using reference = Char&;
  using const_reference = const Char&;
  using pointer = typename std::allocator_traits<Alloc>::pointer;
  using const_pointer = typename std::allocator_traits<Alloc>::const_pointer;
  using iterator = pointer;
  using const_iterator = const_pointer;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

private:

  union storage_t {
    Char ch;
    size_type sz;
  };

  storage_t* storage;

  using sa = typename std::allocator_traits<Alloc>::template rebind_alloc<storage_t>;
  using sa_traits = std::allocator_traits<sa>;

  static storage_t* allocate(size_type n)
  {
    auto a = sa();
    return sa_traits::allocate(
      a,
      ((n+1)*sizeof(Char)+sizeof(size_type)-1) / sizeof(size_type) // (n+1 + size-1)/size, ceil(n+1/size)
      + 2
    ) + 2;
  }

  size_type& sizeref() const
  {
    return storage[-1].sz;
  }

  size_type& capacityref() const
  {
    return storage[-2].sz;
  }

public:

  operator Char*() const
  {
    return reinterpret_cast<Char*>(storage);
  }

  basic_c_string()
    : storage(0)
  {}

  basic_c_string(size_type count, Char ch)
    : storage(allocate(count))
  {
    sizeref() = count;
    capacityref() = count;
    Traits::assign(reinterpret_cast<Char*>(storage), count, ch);
    storage[count].ch = 0;
  }

  ~basic_c_string()
  {
    auto a = sa();
    if (storage)
      sa_traits::deallocate(a, storage-2, capacityref()); // FIXME capacityref is not the allocated count
  }

  size_type size() const
  {
    return storage ? sizeref() : 0;
  }

  size_type capacity() const
  {
    return storage ? capacityref() : 0;
  }

};

using c_string = basic_c_string<char>;

static_assert(sizeof(c_string) == sizeof(char*), "size mismatch?");

int main()
{

  // std::vector<c_string> strs = { {3, 'a'} };

  // const char** p_strs = reinterpret_cast<const char**>(strs.data());

  c_string strs[] {{3, 'a'}};

  char** p_strs = reinterpret_cast<char**>(strs);

  assert(std::string("aaa") == p_strs[0]);

  return 0;
}
