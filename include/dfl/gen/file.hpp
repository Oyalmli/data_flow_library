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
class file : public base_generator<T> {
 private:
  Reader<BUF_SIZE> _reader;
  int more = 1;
  T _curr;

 public:
  /**
   * @brief Construct a new file object
   *
   * @param f FILE*
   */
  file(FILE* f = stdin) : _reader{f} { next(); };
  file(const char* file_path) : _reader{fopen(file_path, "r")} { next(); };

  bool hasNext() const {
    return more > -1;
  }

  T curr() const { return _curr; }

  void next() {
    _curr = _reader.template next<T, word>();
    more += _reader.hasNext() -1;
  }

  MAKE_ITER(file, T);
};
}  // namespace dfl::gen

#endif  // GEN_FILE_HPP