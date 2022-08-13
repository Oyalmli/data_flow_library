/**
 * @file histogram.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Histogram sink class
 * @version 0.1
 * @date 2022-04-28
 *
 * @copyright Copyright (c) 2022
 * @example sink/histogram.cpp
 */
#ifndef DFL_HISTOGRAM_HPP
#define DFL_HISTOGRAM_HPP

namespace dfl::sink {
template <typename T>
class histogram_pipeline : public pipeline_base<histogram_pipeline<T>> {
 public:
  template <typename V, typename...Args>
  void onReceive(V&& value, Args... args) {
    _histogram[value] += 1;
    if constexpr (sizeof...(Args) > 0) {
        onReceive(args...);
    }
  }

  histogram_pipeline(T val) : _histogram(val) {}

 private:
  T _histogram;
};

/**
 * Pipe component for creating a histogram of the incoming values
 * @param map
 * @return itself
 */
template <typename T>
histogram_pipeline<T> histogram(T &&val) {
  return histogram_pipeline<T>{val};
}

}  // namespace dfl::sink

#endif /* DFL_HISTOGRAM_HPP */