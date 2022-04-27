#ifndef DVFW_GEN_VALUE_HPP
#define DVFW_GEN_VALUE_HPP

namespace dvfw {
namespace gen {

template <typename T>
class value : public base_generator<T> {
    public:
    using value_type = T;
    using Iterator = GenIterator<value<T>, T>;
    T _itVal;

    value(T value = 0) : _itVal{value} {};

    bool hasNext() { return true; }

    T next() {
        return _itVal;
    }

    Iterator begin() { return Iterator(this); }
    Iterator end() { return Iterator(nullptr); }
};
}  // namespace gen
}  // namespace dvfw

#endif
