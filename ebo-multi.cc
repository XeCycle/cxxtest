struct A {};
struct B {};

struct T : A, B {};

static_assert(sizeof(T) == 1, "");
