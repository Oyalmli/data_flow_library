/**
 * @file for_each.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief For each sink class
 * @version 0.1
 * @date 2022-04-28
 *
 * @copyright Copyright (c) 2022
 * @example sink/min.cpp
 */
#ifndef DFL_SINK_MIN_HPP
#define DFL_SINK_MIN_HPP

namespace dfl::sink {
template <typename T>
class min_pipeline : public pipeline_base<min_pipeline<T>> {
  template <typename Head0, typename Head1, typename... Tail>
  constexpr auto min_val(Head0 &&head0, Head1 &&head1, Tail &&...tail) {
    if constexpr (sizeof...(tail) == 0) {
      return head0 < head1 ? head0 : head1;
    } else {
      return min_val(min_val(head0, head1), tail...);
    }
  }

 public:
  template <typename... V>
  void onReceive(V &&...value) {
    _min = min_val(_min, value...);
  }

  min_pipeline(T val) : _min(val) {}

 private:
  T _min;
};

/**
 * Pipe component for running a function for each element of a pipeline
 * @param function
 * @return itself
 */
template <typename T>
min_pipeline<T> min(T &&val) {
  return min_pipeline<T>{val};
}

}  // namespace dfl::sink

#endif /* DFL_SINK_MIN_HPP */