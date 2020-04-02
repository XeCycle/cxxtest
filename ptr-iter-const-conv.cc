#include <type_traits>

static_assert(std::is_convertible_v<int (&)[], int const (&)[]>);

struct B {};
struct D : B {};

static_assert(std::is_convertible_v<D*, B*>);
static_assert(!std::is_convertible_v<D (&)[], B (&)[]>);
static_assert(std::is_convertible_v<D (&)[], D const (&)[]>);
