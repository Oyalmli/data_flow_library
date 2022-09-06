/**
 * @file get_var.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Set state pipeline class
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022
 * @example pipe/get_var.cpp
 */
#ifndef DFL_PIPE_GET_VAR_HPP
#define DFL_PIPE_GET_VAR_HPP

namespace dfl::pipe {
template <typename State>
class get_var_pipe : public dfl_base {
   public:
    template <typename Value, typename TailPipeline>
    void onReceive(Value&& value, TailPipeline&& tailPipeline) {
        send(FWD(state_), tailPipeline);
    }
    /**
     * @brief Sets the state of the given variable
     * 
     * EXAMPLE:
     * int last = 0;
     * gen::range(100)
     * >>= pipe::set_var(last) >>= sink::hole();
     * printf("%d\n", max);

    * @tparam State 
    * @param state 
    * @return set_var_pipe<State> 
    */
    explicit get_var_pipe(State state) : state_(state) {}

   private:
    State state_;
};
template <typename State>
get_var_pipe<State> get_var(State&& state) {
    return get_var_pipe<State>{state};
}
}  // namespace dfl::pipe

#endif /* DFL_PIPE_GET_STATE_HPP */