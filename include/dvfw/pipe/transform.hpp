/**
 * @file transform.hpp
 * @author Jonathan Boccara
 * @brief Transform pipeline class
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DVFW_TRANSFORM_HPP
#define DVFW_TRANSFORM_HPP

#include "dvfw/helpers/invoke.hpp"

namespace dvfw::pipe {
template <typename Function>
class transform_pipe : public dvfw_base {
   public:
    template <typename... Values, typename TailPipeline>
    void onReceive(Values&&... values, TailPipeline&& tailPipeline) {
        send(detail::invoke(function_.get(), FWD(values)...), tailPipeline);
    }

    explicit transform_pipe(Function function) : function_(function) {}

   private:
    detail::assignable<Function> function_;
};
/**
 * @brief Transforms the value using the function and forwards the returned value
 * 
 * @tparam Function 
 * @param function 
 * @return transform_pipe<Function> 
 */
template <typename Function>
transform_pipe<Function> transform(Function&& function) {
    return transform_pipe<Function>{function};
}
};  // namespace dvfw::pipe

#endif /* DVFW_TRANSFORM_HPP */