#ifndef GEN_FILE_HPP
#define GEN_FILE_HPP

#include "../util/IO.hpp"

namespace dvfw {
namespace gen {
template <typename T, bool word = true>
class file : public base_generator<T>, base_iterator<file<T, word>, T> {
   public:
    using value_type = T;
    using difference_type = bool;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::forward_iterator_tag;

   private:
    Reader<128> _reader;

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
        return _reader.hasNext();
    }

    file begin(){ return *this; }
    file end(){ return *this; }
    file operator++(){ next(); return *this; }
    file operator++(int){ file f = *this; ++*this; return f; }
    bool operator!=(const file& it){ return hasNext(); }
    T operator*(){ return _itVal; }
};
}  // namespace gen
}  // namespace dvfw

#endif  // GEN_FILE_HPP