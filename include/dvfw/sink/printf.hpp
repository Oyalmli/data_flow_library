#ifndef DVFW_PRINTF_HPP
#define DVFW_PRINTF_HPP

#include <functional>

#include "dvfw/base.hpp"

namespace dvfw {
namespace sink {
template <typename Fmt>
class printf_pipeline : public pipeline_base<printf_pipeline<Fmt>> {
   public:
    template <typename T>
    void onReceive(T&& value) {
        printf(_fmt, value);
    }

    explicit printf_pipeline(Fmt* fmt) : _fmt(fmt) {}

   private:
    const Fmt* _fmt;
};

template <typename Fmt>
printf_pipeline<Fmt> printf(Fmt* fmt) {
    return printf_pipeline<Fmt>(fmt);
}
}
}  // namespace dvfw

#endif /* DVFW_PRINTF_HPP */