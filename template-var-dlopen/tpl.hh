#ifndef TPL_H
#define TPL_H

template <class T>
struct tplc {
  static int const value = 0;
};

template <class T>
int const tplc<T>::value;

struct T;

#endif /* TPL_H */
