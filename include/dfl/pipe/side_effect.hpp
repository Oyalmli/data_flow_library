/**
 * @file side_effect.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Side effect pipeline class
 * @version 0.1
 * @date 2022-04-28
 *
 * @copyright Copyright (c) 2022
 * @example pipe/side_effect.cpp
 */
#ifndef DFL_SIDE_EFFECT_HPP
#define DFL_SIDE_EFFECT_HPP

namespace dfl::pipe {
template <typename Function>
class side_effect_pipe : public dfl_base {
 public:
  template <typename... Values, typename TailPipeline>
  void onReceive(Values&&... values, TailPipeline&& tailPipeline) {
    function_();
    send(FWD(values)..., tailPipeline);
  }

  explicit side_effect_pipe(Function function) : function_(function) {}

 private:
  detail::assignable<Function> function_;
};
/**
 * @brief Runs a side effect function. The values will be passed on, but the
 * function will be run, taking no arguments.
 *
 * @tparam Function
 * @param function
 * @return transform_pipe<Function>
 */
template <typename Function>
side_effect_pipe<Function> side_effect(Function&& function) {
  return side_effect_pipe<Function>{function};
}
}  // namespace dfl::pipe

#endif /* DFL_SIDE_EFFECT_HPP */