/**
 * @file range.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Range generator class
 * @version 0.1
 * @date 2022-04-27
 *
 * @copyright Copyright (c) 2022
 * @example gen/range.cpp
 */
#ifndef DFL_GEN_RANGE_HPP
#define DFL_GEN_RANGE_HPP

namespace dfl::gen {
template <typename T>
class range : public base_generator<T> {

 private:
  T _min, _max, _step, _curr;

 public:

  /**
   * @brief Construct a range generator
   *
   */

  constexpr range(T max=0) 
    : _min{0}, _max(max), _step(1), _curr(0) 
    {};
  constexpr range(T min, T max, T step=1)
    : _min(min), _max(max), _step(step), _curr(min) 
    {};
  
  bool hasNext() const { return _max > _curr; };
  T curr() const { return _curr; }
  void next() { _curr += _step; }
  MAKE_ITER(range, T);
};
}  // namespace dfl::gen

#endif  // DFL_GEN_RANGE_HPP
