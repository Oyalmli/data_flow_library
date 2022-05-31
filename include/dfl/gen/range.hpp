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
class range : public base_generator<range<T>, T> {
 private:
  T _min, _max, _step, _curr;

 public:
  /**
   * @brief Construct a range generator
   *
   */
  range() = default;
  range(T max) : _min{0}, _max{max}, _step{1}, _curr{0} {};
  range(T min, T max) : _min{min}, _max{max}, _step{1}, _curr{min} {};
  range(T min, T max, T step)
      : _min{min}, _max{max}, _step{step}, _curr{min} {};
  IT(range<T>, T);

  bool hasNext() { return _max > _curr; }

  T next() { return (_curr += _step); }

  T curr() { return _curr; }
};
}  // namespace dfl::gen

#endif  // DFL_GEN_RANGE_HPP
