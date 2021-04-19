template <class T>
struct obj_t {};

obj_t() -> obj_t<int>;

auto x = obj_t();
