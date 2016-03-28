#include <type_traits>

struct vbase {};
struct behaviour_a : virtual vbase {};
struct behaviour_b : virtual vbase {};
struct final_class : behaviour_a, behaviour_b {};

int main(int argc, char *argv[])
{

  static_assert(std::is_trivially_copyable<final_class>(), "trivial");

  return 0;
}
