template <class T>
struct X {
  template <class U>
  void f();
};

template <class T>
template <class U>
void X<T>::f()
{}
