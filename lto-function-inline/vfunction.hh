#pragma once

#include <cstddef>
#include <new>
#include <stdexcept>
#include <type_traits>

template <class> struct function;

template <class Ret, class... Arg>
struct function<Ret(Arg...)> {

  struct vbase {
    virtual Ret call(Arg...) = 0;
    virtual ~vbase() = default;

    std::max_align_t buf[7];
  };

  template <class F>
  struct vimpl : vbase {
    vimpl(F f)
    {
      new ((void*)this->buf) F(f);
    }

    ~vimpl()
    {
      ((F*)this->buf)->~F();
    }

    Ret call(Arg... arg) override
    {
      return (*((F*)this->buf))(arg...);
    }
  };

  struct vempty : vbase {
    Ret call(Arg...)
    {
      throw std::runtime_error("empty function");
    }
  };

  struct empty_t {};
  typename std::aligned_union<0, empty_t, vbase>::type store;

  template <class F>
  function(F f)
  {
    using t = vimpl<F>;
    ::new ((void*)&store) t(f);
  }

  ~function()
  {
    ((vbase&)store).~vbase();
  }

  Ret operator()(Arg... arg)
  {
    return ((vbase&)store).call(arg...);
  }

};
