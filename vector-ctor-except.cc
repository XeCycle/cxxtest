#include <cstdio>
#include <cstddef>
#include <vector>

struct throwing_copy {
  throwing_copy() = default;
  static size_t counter;
  throwing_copy(throwing_copy&&) noexcept = default;
  throwing_copy(const throwing_copy&)
  {
    ++counter;
    if (counter >= 5)
      throw 1;
  }
  ~throwing_copy()
  {
    fprintf(stderr, "destroying %p\n", this);
    fflush(stderr);
  }
};

size_t throwing_copy::counter = 0;

template <class T>
struct ptr_input_iterator {

  using value_type = T;
  using difference_type = std::ptrdiff_t;
  using pointer = T*;
  using reference = T&;
  using iterator_category = std::input_iterator_tag;

  T* p;

  reference operator*() const
  {
    return *p;
  }

  ptr_input_iterator& operator++()
  {
    ++p;
    return *this;
  }

  bool operator==(const ptr_input_iterator& other)
  {
    return p == other.p;
  }

  bool operator!=(const ptr_input_iterator& other)
  {
    return p != other.p;
  }

};

int main()
{

  throwing_copy src[10];
  using iter = ptr_input_iterator<throwing_copy>;

  try {
    std::vector<throwing_copy> vec(iter{src}, iter{src+10});
  } catch(int) {
  }

  return 0;
}
