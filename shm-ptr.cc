#include <cstddef>

// may be useful in SHM data structures?

struct shmptr_t {
  ptrdiff_t d;
  void* get()
  {
    return d + (char*)this;
  }
};
