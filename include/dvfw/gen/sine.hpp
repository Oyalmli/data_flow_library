#ifndef GEN_SINE_HPP
#define GEN_SINE_HPP

#include <type_traits>
#include <cmath>

namespace dvfw {
namespace gen {

template <typename T, 
    typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
class sine: public base_generator<T> {
   private:
    T _freq, _ampl, _yOffset, _cnt = 0;

    float getSine() {
        return (_ampl * sin(2 * M_PI * _freq * (_cnt++) + 0) + _yOffset);
    }

   public:
    sine() = default;
    sine(T freq, T ampl, T yOffset) : _freq{freq}, _ampl{ampl}, _yOffset{yOffset} {};

    bool hasNext() {
        return true;
    }

    T next() {
        return getSine();
    }
};
}  // namespace gen
}  // namespace dvfw

#endif  // GEN_SINE_HPP
