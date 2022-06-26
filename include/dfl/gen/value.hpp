/**
 * @file value.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Value generator class
 * @version 0.1
 * @date 2022-04-27
 *
 * @copyright Copyright (c) 2022
 * @example gen/value.cpp
 */
#ifndef DFL_GEN_VALUE_HPP
#define DFL_GEN_VALUE_HPP

namespace dfl::gen {

template <typename T>
class value : public base_generator<T> {
 private:
  T _curr;

 public:
  /**
   * @brief Repeats the set value
   *
   * @param value to be repeated
   */
  value(T value = 0) : _curr{value} {};

  bool hasNext() const { return true; }
  T curr() const { return _curr; }
  void next() { }
  
  MAKE_ITER(value, T);
};
}  // namespace dfl::gen

#endif
