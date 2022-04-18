#ifndef DVFW_GEN_ITER_HPP
#define DVFW_GEN_ITER_HPP

namespace dvfw {
namespace gen {

template <typename Gen>
class It {
   public:
    Gen _gen;
    decltype(_gen.next()) _curr;
    
    It(Gen gen) : _gen{gen} {
        _curr = _gen.next();
    }

    It begin(){ return *this; }
    It end() { return *this; }
    It operator++(){ _curr = _gen.next(); return *this; }
    It operator++(int){ It  bg = *this; ++*this; return bg; }
    bool operator!=(const It& it){ return _gen.hasNext(); }
    decltype(_gen.next()) operator*(){ return _curr; }
};

};  // namespace gen
};  // namespace dvfw

#endif /* DVFW_BASE_ITER_HPP */