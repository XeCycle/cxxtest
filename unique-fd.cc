#include <utility>

#include <unistd.h>

struct unique_fd {

  int fd;

  constexpr unique_fd()
    : fd(-1)
  {}

  constexpr explicit unique_fd(int _fd)
    : fd(_fd)
  {}

  constexpr operator int() const
  {
    return fd;
  }

  ~unique_fd()
  {
    if (fd >= 0)
      close(fd);
  }

  unique_fd(const unique_fd&) = delete;
  unique_fd& operator=(const unique_fd&) = delete;

  unique_fd(unique_fd&& other) noexcept
    : fd(other.fd)
  {
    other.fd = -1;
  }

  unique_fd& operator=(unique_fd&& other)
  {
    if (fd >= 0)
      close(fd);
    fd = other.fd, other.fd = -1;
    return *this;
  }

};

void swap(unique_fd& a, unique_fd& b) noexcept
{
  using std::swap;
  swap(a.fd, b.fd);
}
