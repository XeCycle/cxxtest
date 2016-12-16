struct alignas(void*) base
{};

struct derived : base {
  void* p;
};

struct smaller : base {
  char x;
};

static_assert(sizeof(derived) == sizeof(void*), "");
static_assert(sizeof(smaller) == sizeof(void*), "");
