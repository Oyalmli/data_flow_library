#ifndef DVFW_GEN_ITER_HPP
#define DVFW_GEN_ITER_HPP

namespace dvfw {
namespace gen {
template <typename Gen>
class GenIterator {
   public:
    using value_type = typename Gen::value_type;
    using difference_type = bool;
    using pointer_type = value_type*;
    using reference_type = value_type&;
    using iterator_category = std::input_iterator_tag;

    Gen* _range;

   public:
    GenIterator(Gen* range) : _range{range} {};

    GenIterator& operator++() {
        _range->next();
        return *this;
    }

    bool operator!=(GenIterator& other) {
        return _range->hasNext();
    }

    value_type operator*() {
        return _range->_itVal;
    }
};
};  // namespace gen
};  // namespace dvfw

#endif /* DVFW_BASE_ITER_HPP */