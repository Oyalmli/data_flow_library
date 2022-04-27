#ifndef DVFW_GEN_ITER_HPP
#define DVFW_GEN_ITER_HPP

#include <iterator>

namespace dvfw {
namespace gen {
template <class Gen, typename T>
class GenIterator : public std::iterator<std::input_iterator_tag, T, bool, T*, T&> {
    Gen* _range;

   public:
    explicit GenIterator(Gen* range) : _range{range} {};

    GenIterator& operator++() {
        _range->next();
        return *this;
    }

    bool operator!=(GenIterator& other) {
        return _range->hasNext();
    }

    T operator*() {
        return _range->_itVal;
    }
};
};  // namespace gen
};  // namespace dvfw

#endif /* DVFW_BASE_ITER_HPP */