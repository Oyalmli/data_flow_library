/**
 * @file scanl.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Scanl pipeline class
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DFL_SCANL_HPP
#define DFL_SCANL_HPP

namespace dfl::pipe {
template <typename Function, typename State>
class scanl_pipe : public dfl_base {
   public:
    template <typename... Values, typename TailPipeline>
    void onReceive(Values&&... values, TailPipeline&& tailPipeline) {
        state_ = function_(state_, values...);
        send(FWD(state_), tailPipeline);
    }

    explicit scanl_pipe(Function function, State initState) : function_(function), state_(initState) {}

   private:
    Function function_;
    State state_;
};

/**
 * @brief Scanl function for applying funciton with a kept state
 * 
 * Applies a function to every element of a range with the internal state as the first arugment, and the value from the range as the other
 * 
 * @tparam Function 
 * @tparam State 
 * @param function 
 * @param initState 
 * @return scanl_pipe<Function, State> 
 */
template <typename Function, typename State>
scanl_pipe<Function, State> scanl(Function&& function, State initState) {
    return scanl_pipe<Function, State>{function, initState};
}
}  // namespace dfl::pipe

#endif /* DFL_SCANL_HPP */