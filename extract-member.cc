template <class Struct, class Member>
Struct deduce_memptr_struct_type(Member Struct::*);

template <class Struct, class Member>
Member deduce_memptr_member_type(Member Struct::*);

template <class Struct, class Member, Member Struct::* memptr>
struct extract_member_t_static {
  constexpr Member operator()(Struct s) const
  {
    return s.*memptr;
  }
};

#define extract_member_static(memptr)                                   \
  extract_member_t_static                                               \
  <decltype(deduce_memptr_struct_type(memptr)),                         \
   decltype(deduce_memptr_member_type(memptr)),                         \
   memptr>()

template <class Struct, class Member>
struct extract_member_t_dynamic {
  Member Struct::* memptr;
  constexpr Member operator()(Struct s) const
  {
    return s.*memptr;
  }
};

template <class Struct, class Member>
extract_member_t_dynamic<Struct, Member>
extract_member_dynamic(Member Struct::* memptr)
{
  return { memptr };
}
