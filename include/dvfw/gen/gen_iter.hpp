#ifndef DVFW_GEN_ITER_HPP
#define DVFW_GEN_ITER_HPP

namespace dvfw {
namespace gen {

template <class Gen>
class It {
   public:
    using value_type = typename Gen::T;
    using difference_type = bool;
    using pointer = value_type*;
    using reference = value_type&;
    using iterator_category = std::forward_iterator_tag;

   public:
    Gen _gen;
    value_type _curr;

    It(Gen gen) : _gen{gen} {
        _curr = _gen.next();
    }

    It begin() { return *this; }
    It end() { return *this; }
    It operator++() {
        _curr = _gen.next();
        return *this;
    }
    It operator++(int) {
        It bg = *this;
        ++*this;
        return bg;
    }
    bool operator!=(const It& it) { return _gen.hasNext(); }
    value_type operator*() { return _curr; }
};

};  // namespace gen
};  // namespace dvfw

#endif /* DVFW_BASE_ITER_HPP */