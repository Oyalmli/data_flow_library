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
template <typename T, bool word = true, size_t BUF_SIZE=128>
class file : public base_generator<file<T, word, BUF_SIZE>, T> {
  using class_type = file<T, word, BUF_SIZE>;

 private:
  Reader<BUF_SIZE> _reader;
  bool more = true;
  T _curr;

 public:
  /**
   * @brief Construct a new file object
   *
   * @param f FILE*
   */
  file(FILE* f = stdin) : _reader{f} { _curr = next(); };
  IT(class_type, T);

  bool hasNext() {
    bool temp = more;
    more &= _reader.hasNext();
    return temp;
  }

  T next() {
    _curr = _reader.template next<T, word>();
    return _curr;
  }

  T curr() { return _curr; }
};
}  // namespace dfl::gen

#endif  // GEN_FILE_HPP