#ifndef GEN_MOD_TAKE_HPP
#define GEN_MOD_TAKE_HPP

namespace dvfw {
namespace gen {
template <typename Gen>
class take : public Gen {
    Gen _gen;
    size_t _num;
    size_t _taken{0};

   public:
    take(size_t num, Gen generator) : _gen{generator}, _num{num} {}

    bool hasNext() {
        return (_taken < _num);
    }

    decltype(_gen.next()) next () {
        _taken++;
        return _gen.next();
    }
};
}  // namespace gen
}  // namespace dvfw

#endif  // GEN_MOD_SLICE_HPP
