#include <boost/smart_ptr/intrusive_ptr.hpp>

namespace lib {

struct U {};

} // namespace lib

namespace me {

struct T : U {
  size_t count = 0;
};

void intrusive_ptr_add_ref(T* p)
{
  ++p->count;
}

void intrusive_ptr_release(T* p)
{
  if (--p->count == 0)
    delete p;
}

} // namespace me

int main()
{

  boost::intrusive_ptr<me::T> up = new me::T();

  boost::intrusive_ptr<lib::U> vp = up;

  return 0;
}
