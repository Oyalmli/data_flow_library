#ifndef DVFW_GEN_RANGE_HPP
#define DVFW_GEN_RANGE_HPP

namespace dvfw {
namespace gen {
template <typename T>
class range : public base_generator<T>, base_iterator<range<T>, T> {
   public:
    using value_type = T;
    using difference_type = bool;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::forward_iterator_tag;

   private:
    T _min, _max, _step, _curr;

   public:
    T _itVal;

    range() = default;
    range(T max) : _min{0}, _max{max}, _step{1}, _curr{0}, _itVal{0} {};
    range(T min, T max) : _min{min}, _max{max}, _step{1}, _curr{min}, _itVal{min} {};
    range(T min, T max, T step) : _min{min}, _max{max}, _step{step}, _curr{min}, _itVal{min} {};

    bool hasNext() {
        return _max > _curr;
    }

    T next() {
        _curr += _step;
        _itVal = _curr;
        return _itVal;
    }

    range begin() { return *this; }
    range end() { return *this; }

    range operator++() {
        next();
        return *this;
    }

    range operator++(int) {
        range r = *this;
        ++*this;
        return r;
    }
    bool operator!=(const range& it) { return hasNext(); }
    T operator*() { return _itVal; }
};
}  // namespace gen
}  // namespace dvfw

#endif  // DVFW_GEN_RANGE_HPP
