#ifndef DVFW_GEN_VALUE_HPP
#define DVFW_GEN_VALUE_HPP

namespace dvfw {
namespace gen {

template <typename T>
class value : public base_generator<T> {
   private:
    std::size_t _numVals;
    std::size_t _sent{0};

   public:
    T _itVal;

    value(T value = 0) : _itVal{value} {};

    bool hasNext() { return true; }
    
    T next() {
        return _itVal;
    }

    value begin(){ return *this; }
    value end() { return *this; }
    value operator++(){ return *this; }
    value operator++(int){ return *this; }
    bool operator!=(const value& it){ return hasNext(); }
    T operator*(){ return _itVal; }
};
}  // namespace gen
}  // namespace dvfw

#endif
