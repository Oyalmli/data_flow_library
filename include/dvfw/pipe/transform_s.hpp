/**
 * @file transform_s.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Transform with state pipeline class
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DVFW_TRANSFORM_S_HPP
#define DVFW_TRANSFORM_S_HPP

namespace dvfw::pipe {
template <typename Function, typename State>
class transform_s_pipe : public dvfw_base {
   public:
    template <typename... Values, typename TailPipeline>
    void onReceive(Values&&... values, TailPipeline&& tailPipeline) {
        send(FWD(function_(values..., state_)), tailPipeline);
    }

    explicit transform_s_pipe(Function function, State state) : function_(function), state_(state) {}

   private:
    Function function_;
    State state_;
};

/**
 * @brief Applies the function on the value and state, allowing the possibility of changing the state
 * 
 * @tparam Function 
 * @tparam State 
 * @param function 
 * @param state 
 * @return transform_s_pipe<Function, State> 
 */
template <typename Function, typename State>
transform_s_pipe<Function, State> transform_s(Function&& function, State&& state) {
    return transform_s_pipe<Function, State>{function, state};
}
};  // namespace dvfw::pipe

#endif /* DVFW_TRANSFORM_S_HPP */