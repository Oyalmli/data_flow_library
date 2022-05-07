/**
 * @file transform_t.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-05-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DVFW_TRANSFORM_T_HPP
#define DVFW_TRANSFORM_T_HPP

#include "dvfw/helpers/invoke.hpp"
#include <tuple>

namespace dvfw::pipe {
template <typename Function>
class transform_t_pipe : public dvfw_base {
   public:
    template <typename Tuple, typename TailPipeline>
    void onReceive(Tuple&& values, TailPipeline&& tailPipeline) {
        auto func = [&tailPipeline](auto const&... e) -> void {
            send(FWD(e)..., tailPipeline);
        };
        std::apply(func, values);
        //detail::for_each(FWD(values), [&tailPipeline](auto&& value) { send(value, tailPipeline); });
        //
    }

    explicit transform_t_pipe(Function function) : function_(function) {}

   private:
    detail::assignable<Function> function_;
};
/**
 * @brief Transforms the value using the function and forwards the returned value
 * 
 * @tparam Function 
 * @param function 
 * @return transform_t_pipe<Function> 
 */
template <typename Function>
transform_t_pipe<Function> transform_t(Function&& function) {
    return transform_t_pipe<Function>{function};
}
}  // namespace dvfw::pipe

#endif /* DVFW_TRANSFORM_T_HPP */