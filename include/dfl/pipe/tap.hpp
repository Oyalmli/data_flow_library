/**
 * @file tap.hpp
 * @author Jonathan Boccara
 * @brief Tap pipeline class
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022
 * @example pipe/tap.cpp
 */
#ifndef DFL_TAP_HPP
#define DFL_TAP_HPP

namespace dfl::pipe {
template <typename Function>
class tap_pipe : public dfl_base {
   public:
    template <typename Value, typename TailPipeline>
    void onReceive(Value&& value, TailPipeline&& tailPipeline) {
        function_(FWD(value));
        send(FWD(value), tailPipeline);
    }

    template <typename Value>
    void onReceive(Value&& value) {
        function_(FWD(value));
    }

    explicit tap_pipe(Function function) : function_(function) {}

   private:
    detail::assignable<Function> function_;
};
/**
 * @brief Forwards the value to a function, as well as the next pipe
 * 
 * @tparam Function 
 * @param function 
 * @return tap_pipe<std::decay_t<Function>> 
 */
template <typename Function>
tap_pipe<std::decay_t<Function>> tap(Function&& function) {
    return tap_pipe<std::decay_t<Function>>(FWD(function));
}
}  // namespace dfl::pipe

#endif /* DFL_TAP_HPP */