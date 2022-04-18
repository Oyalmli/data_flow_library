#ifndef GEN_MOD_TAKE_HPP
#define GEN_MOD_TAKE_HPP

namespace dvfw {
namespace gen {
template <typename Gen>
class take {
    Gen _gen;
    size_t _num;
    size_t _taken{0};
    
   public:

    take(size_t num, Gen generator) : _gen{generator}, _num{num} {}

    bool hasNext() {
        return _gen.hasNext() && (_taken < _num);
    }

    decltype(_gen.next()) next() {
        _taken++;
        _gen.next();
        return _gen._itVal;
    }

    take begin() { return *this; }
    take end() { return *this; }
    take operator++(){
        next();
        return *this;
    }
    bool operator!=(const take& it){ return hasNext(); }
    decltype(_gen._itVal) operator*(){ return _gen._itVal; }
};
}  // namespace gen
}  // namespace dvfw

#endif  // GEN_MOD_SLICE_HPP
