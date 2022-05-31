/**
 * @file file.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief File generator class
 * @version 0.1
 * @date 2022-04-27
 *
 * @copyright Copyright (c) 2022
 * @example gen/file.cpp
 */
#ifndef GEN_FILE_HPP
#define GEN_FILE_HPP

#include "../util/IO.hpp"

namespace dfl::gen {
template <typename T, bool word = true>
class file : public base_generator<file<T, word>, T> {
  using iterator = GenIterator<file<T, word>, T>;

 private:
  Reader<128> _reader;
  bool more = true;
  T _curr;

 public:
  /**
   * @brief Construct a new file object
   *
   * @param f FILE*
   */
  file(FILE* f = stdin) : _reader{f} { _curr = next(); };

  bool hasNext() {
    if (!_reader.hasNext() && more) {
      more = false;
      return true;
    }
    return more;
  }

  T next() {
    _curr = _reader.next<T, word>();
    return _curr;
  }

  T curr() { return _curr; }

  iterator begin() { return iterator(this); }
  iterator end() { return iterator(nullptr); }
};
}  // namespace dfl::gen

#endif  // GEN_FILE_HPP