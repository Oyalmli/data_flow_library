#ifndef GEN_FILE_HPP
#define GEN_FILE_HPP

#include "../util/IO.hpp"

namespace dvfw {
namespace gen {
template <typename T, bool word = true>
class file {
   public:
    using value_type = T;
    using Iterator = GenIterator<file<T, word>>;

   private:
    Reader<128> _reader;
    bool more = true;

   public:
    T _itVal;
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
}  // namespace gen
}  // namespace dvfw

#endif  // GEN_FILE_HPP