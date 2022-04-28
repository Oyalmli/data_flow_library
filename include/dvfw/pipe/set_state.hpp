/**
 * @file set_state.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Set state pipeline class
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DVFW_SET_STATE_HPP
#define DVFW_SET_STATE_HPP

namespace dvfw::pipe {
template <typename Function, typename State>
class set_state_pipe : public dvfw_base {
   public:
    template <typename... Values, typename TailPipeline>
    void onReceive(Values&&... values, TailPipeline&& tailPipeline) {
        function_(values..., state_);
        send(FWD(values)..., tailPipeline);
    }

    explicit set_state_pipe(Function function, State state) : function_(function), state_(state) {}

   private:
    Function function_;
    State state_;
};

/**
 * @brief Sets the state of the given variable using the function provided
 * 
 * EXAMPLE:
 * int max = 0;
 * auto generator = gen::range(100);
 * auto pipeline 
 * =   pipe::set_state([](auto i, auto& max_){ max_ = i > max_ ? i : max_; }, max)
 * >>= sink::hole();
 * generator >>= pipeline;
 * printf("%d\n", max);

 * @tparam Function 
 * @tparam State 
 * @param function 
 * @param state 
 * @return set_state_pipe<Function, State> 
 */
template <typename Function, typename State>
set_state_pipe<Function, State> set_state(Function&& function, State&& state) {
    return set_state_pipe<Function, State>{function, state};
}
};  // namespace dvfw::pipe

#endif /* DVFW_SET_STATE_HPP */