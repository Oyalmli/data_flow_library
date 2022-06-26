/**
 * @file counter.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Counter generator class
 * @version 0.1
 * @date 2022-05-09
 * 
 * @copyright Copyright (c) 2022
 * @example gen/counter.cpp
 */

#ifndef GEN_COUNTER_HPP
#define GEN_COUNTER_HPP

namespace dfl::gen {
template <typename T>
class counter : public base_generator<T> {
  T _curr;

 public:
  /**
   * @brief Counts from 0
   * 
   * @param max 
   */
  counter() : _curr{0} {}
  bool hasNext() const { return true; }
  T curr() const { return _curr; }
  void next() { _curr++; }

  MAKE_ITER(counter, T);
};
} // namespace dfl::gen

#endif //GEN_COUNTER_HPP