struct base {
  int x;
};

template <int n>
struct derived : base {

  constexpr int operator()() const
  {
    return x+n;
  }

};

int main(int argc, char *argv[])
{

  base x { 42 };

  auto& b = static_cast<derived<3>&>(x);

  return b();
}
