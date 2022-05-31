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
class value : public base_generator<value<T>, T> {
 private:
  T _curr;

 public:
  /**
   * @brief Repeats the set value
   *
   * @param value to be repeated
   */
  value(T value = 0) : _curr{value} {};
  IT(value<T>, T);

  /**
   * @brief Returns true if the generator has more values
   *
   * @return true
   */
  bool hasNext() { return true; }

  /**
   * @brief The next value from the iterator
   *
   * @return T
   */
  T next() { return _curr; }

  T curr() { return _curr; }
};
}  // namespace dfl::gen

#endif
