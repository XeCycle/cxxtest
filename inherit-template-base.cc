template <class T>
class Y {
public:
  void f() {}
};

template <class T>
class X : public Y<T> {
public:
  X();
};

template <class T>
X<T>::X()
{
  this->f();
}

struct Z {};

int main()
{         
  X<Z> obj;
  return 0;
}
