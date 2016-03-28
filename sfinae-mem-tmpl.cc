template <class T, template <class...> class>
struct any_template {
  using type = T;
};

template <class UnboundSink>
auto operate_on_usink(UnboundSink s)
  -> typename any_template<int, UnboundSink::template bind_t>::type
{
  return 3;
}

struct usink {
  template <class>
  struct bind_t {};
};

struct other {};

int main()
{

  return operate_on_usink(usink());

}
