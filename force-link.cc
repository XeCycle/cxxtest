template <class T>
void target_fn();

template <class T>
struct ensure_link {

private:
  static void x() __attribute__((used)) { target_fn<T>(); }

};

int main()
{
  ensure_link<int>();
}
