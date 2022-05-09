/**
 * @file sine.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Sine generator class
 * @version 0.1
 * @date 2022-04-28
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef GEN_SINE_HPP
#define GEN_SINE_HPP

#include <cmath>

namespace dvfw::gen {

template <typename T,
          typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
class sine : public base_generator<sine<T>, T> {
 private:
  T _freq, _ampl, _yOffset, _curr;
  long long _cnt = 0;

  float getSine() {
    return (_ampl * sin(2 * M_PI * _freq * (_cnt++) + 0) + _yOffset);
  }

 public:
  /**
   * @brief Creates a sine wave generator with as set frequency, amplitude and
   * offset.
   *
   * @param freq
   * @param ampl
   * @param yOffset
   */
  sine(T freq = 0.0, T ampl = 1.0, T yOffset = 0.0)
      : _freq{freq}, _ampl{ampl}, _yOffset{yOffset} {
    _curr = next();
  };
  IT(sine<T>, T);

  bool hasNext() { return true; }

  T next() {
    _curr = getSine();
    return _curr;
  }

  T curr() { return _curr; }
};
}  // namespace dvfw::gen

#endif  // GEN_SINE_HPP
