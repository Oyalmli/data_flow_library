/**
 * @file set_var.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Set var pipeline class
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022
 * @example pipe/set_var.cpp
 */
#ifndef DFL_PIPE_SET_VAR_HPP
#define DFL_PIPE_SET_VAR_HPP

namespace dfl::pipe {
template <typename State>
class set_var_pipe : public dfl_base {
   public:
    template <typename Value, typename TailPipeline>
    void onReceive(Value&& value, TailPipeline&& tailPipeline) {
        state_ = value;
        send(FWD(value), tailPipeline);
    }
    /**
     * @brief Sets the state of the given variable
     * @tparam State 
     * @param state 
     * @return set_var_pipe<State> 
     */
    explicit set_var_pipe(State state) : state_(state) {}

   private:
    State state_;
};
template <typename State>
set_var_pipe<State> set_var(State&& state) {
    return set_var_pipe<State>{state};
}
}  // namespace dfl::pipe

#endif /* DFL_SINK_SET_STATE_HPP */