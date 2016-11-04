#include "tpl.hh"

#include <dlfcn.h>

int main()
{

  auto lib = dlmopen(LM_ID_NEWLM, "libtpl.so", RTLD_NOW);

  auto f = reinterpret_cast<bool(*)(int const*)>(dlsym(lib, "f"));

  return !(f(&tplc<T>::value));
}
