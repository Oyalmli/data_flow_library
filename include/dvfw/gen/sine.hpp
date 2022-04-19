#ifndef GEN_SINE_HPP
#define GEN_SINE_HPP

#include <cmath>
#include <type_traits>

namespace dvfw {
namespace gen {

template <typename T, typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
class sine : public base_generator<T>, base_iterator<sine<T>, T> {
   public:
    using value_type = T;
    using difference_type = bool;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::forward_iterator_tag;

   private:
    T _freq, _ampl, _yOffset;
    long long _cnt = 0;

    float getSine() {
        return (_ampl * sin(2 * M_PI * _freq * (_cnt++) + 0) + _yOffset);
    }

   public:
    T _itVal;

    sine(T freq = 0.0, T ampl = 0.0, T yOffset = 0.0) : _freq{freq}, _ampl{ampl}, _yOffset{yOffset} {};

    bool hasNext() {
        return true;
    }

    T next() {
        _itVal = getSine();
        return _itVal;
    }

    sine begin() { return *this; }
    sine end() { return *this; }
    sine operator++() {
        next();
        return *this;
    }
    sine operator++(int) {
        sine s = *this;
        ++*this;
        return s;
    }
    bool operator!=(const sine& it) { return hasNext(); }
    T operator*() { return _itVal; }
};
}  // namespace gen
}  // namespace dvfw

#endif  // GEN_SINE_HPP
