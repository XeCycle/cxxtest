#pragma once

#include <map>

class T {
  struct X;
  std::map<int, X> m;

public:
  T();
  ~T();
};
