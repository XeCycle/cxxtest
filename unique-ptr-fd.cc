#include <memory>

#include <unistd.h>

struct fdint {

  int fd;

  fdint(int _fd)
    : fd(_fd)
  {}

  fdint()
    : fd(-1)
  {}

  fdint(decltype(nullptr))
    : fdint()
  {}

  explicit operator bool() const
  {
    return fd >= 0;
  }

};

bool operator==(fdint a, fdint b)
{
  return a.fd == b.fd || (a.fd < 0 && b.fd < 0);
}

bool operator!=(fdint a, fdint b)
{
  return !(a == b);
}

struct fdint_close {

  using pointer = fdint;

  void operator()(fdint f) const
  {
    ::close(f.fd);
  }
};

using unique_fd = std::unique_ptr<int, fdint_close>;
