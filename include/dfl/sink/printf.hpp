/**
 * @file printf.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Printf sink class
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022
 * @example sink/printf.cpp
 */
#ifndef DFL_PRINTF_HPP
#define DFL_PRINTF_HPP

#include <functional>

namespace dfl::sink {
template <typename Fmt>
class printf_pipeline : public pipeline_base<printf_pipeline<Fmt>> {
   public:
    template <typename... T>
    void onReceive(T&&... value) {
        printf(_fmt, value...);
    }

    explicit printf_pipeline(Fmt* fmt) : _fmt(fmt) {}

   private:
    const Fmt* _fmt;
};

template <typename Fmt>
printf_pipeline<Fmt> printf(Fmt* fmt) {
    return printf_pipeline<Fmt>(fmt);
}
}  // namespace dfl::sink

#endif /* DFL_PRINTF_HPP */