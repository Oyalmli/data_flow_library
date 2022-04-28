/**
 * @file file.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief File generator class
 * @version 0.1
 * @date 2022-04-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef GEN_FILE_HPP
#define GEN_FILE_HPP

#include "../util/IO.hpp"

namespace dvfw::gen {
template <typename T, bool word = true>
class file {
   public:
    using value_type = T;
    using Iterator = GenIterator<file<T, word>, T>;

   private:
    Reader<128> _reader;
    bool more = true;

   public:
    T _itVal;
    /**
     * @brief Construct a new file object
     * 
     * @param f FILE*
     */
    file(FILE* f = stdin) : _reader{f} {
        _itVal = next();
    };

    T next() {
        _itVal = _reader.next<T, word>();
        return _itVal;
    }

    bool hasNext() {
        if(!_reader.hasNext() && more) {
            more = false;
            return true;
        }
        return more;
    }

    Iterator begin() { return Iterator(this); }
    Iterator end() { return Iterator(nullptr); }
};
};  // namespace dvfw::gen

#endif  // GEN_FILE_HPP