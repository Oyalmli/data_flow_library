/**
 * @file for_each.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief For each sink class
 * @version 0.1
 * @date 2022-04-28
 *
 * @copyright Copyright (c) 2022
 * @example sink/max.cpp
 */
#ifndef DFL_SINK_MAX_HPP
#define DFL_SINK_MAX_HPP

namespace dfl::sink {
template <typename T>
class max_pipeline : public pipeline_base<max_pipeline<T>> {
 private:
  template <typename Head0, typename Head1, typename... Tail>
  constexpr auto max_val(Head0 &&head0, Head1 &&head1, Tail &&...tail) {
    if constexpr (sizeof...(tail) == 0) {
      return head0 > head1 ? head0 : head1;
    } else {
      return max_val(max_val(head0, head1), tail...);
    }
  }

 public:
  template <typename... V>
  void onReceive(V &&...value) {
    _max = max_val(_max, value...);
  }

  max_pipeline(T val) : _max(val) {}

 private:
  T _max;
};

/**
 * Pipe component for running a function for each element of a pipeline
 * @param function
 * @return itself
 */
template <typename T>
max_pipeline<T> max(T &&val) {
  return max_pipeline<T>{val};
}

}  // namespace dfl::sink

#endif /* DFL_SINK_MIN_HPP */