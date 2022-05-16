/**
 * @file stride.hpp
 * @author Jonathan Boccara
 * @brief
 * @version 0.1
 * @date 2022-05-11
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef PIPES_STEP_HPP
#define PIPES_STEP_HPP

namespace dfl::pipe {
class stride : public dfl_base {
 public:
  template <typename... Values, typename TailPipeline>
  void onReceive(Values&&... values, TailPipeline&& tailPipeline) {
    if (nbSinceLastStride_ <= 0) {
      send(FWD(values)..., FWD(tailPipeline));
      nbSinceLastStride_ = strideSize_;
    } else {
      --nbSinceLastStride_;
    }
  }

  explicit stride(size_t strideSize)
      : strideSize_{strideSize-1}, nbSinceLastStride_{0} {}

 private:
  size_t strideSize_;
  size_t nbSinceLastStride_;
};
}  // namespace dfl::pipe

#endif /* PIPES_STEP_HPP */