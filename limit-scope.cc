auto x = ([](Dependency a) {
  Foo f(a);
  Bar b(a);
  return f+b;
})({});

long_computation(x);
