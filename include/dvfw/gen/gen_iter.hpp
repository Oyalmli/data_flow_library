#ifndef DVFW_GEN_ITER_HPP
#define DVFW_GEN_ITER_HPP

namespace dvfw {
namespace gen {

template <class Gen>
class It {
   public:
    Gen _gen;
    decltype(_gen.next()) _itVal;

   public:
    using value_type = decltype(_gen.next());
    using difference_type = bool;
    using pointer = value_type*;
    using reference = value_type&;
    using iterator_category = std::forward_iterator_tag;   

    It(Gen gen) : _gen{gen} {
        _itVal = _gen.next();
    }

    It begin() { return *this; }
    It end() { return *this; }
    It operator++() {
        _itVal = _gen.next();
        return *this;
    }
    It operator++(int) {
        It bg = *this;
        ++*this;
        return bg;
    }
    bool operator!=(const It& it) { return _gen.hasNext(); }
    value_type operator*() { return _itVal; }
};

};  // namespace gen
};  // namespace dvfw

#endif /* DVFW_BASE_ITER_HPP */