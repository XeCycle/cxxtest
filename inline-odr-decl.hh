#ifndef INLINE_ODR_DECL_HH
#define INLINE_ODR_DECL_HH

struct T {

  template <class X>
  int f();

  int f1() { return f<int>(); }
  int f2() { return f<double>(); }

};

#endif /* INLINE_ODR_DECL_HH */
