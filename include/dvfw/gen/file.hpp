#ifndef GEN_FILE_HPP
#define GEN_FILE_HPP

#include "reader/reader.hpp"

namespace dvfw {
namespace gen {
template <typename T, bool word = true>
class file : public base_generator<T> {
   private:
    Reader _reader;

   public:
    file() : _reader{stdin} {};
    file(FILE* f) : _reader{f} {};

    T next() {
        return _reader.next<T, word>();
    }

    bool hasNext() {
        return _reader.hasNext();
    }
};
}  // namespace gen
}  // namespace dvfw

#endif  // GEN_FILE_HPP