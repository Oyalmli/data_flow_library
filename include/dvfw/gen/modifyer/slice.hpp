#ifndef GEN_MOD_TAKE_HPP
#define GEN_MOD_TAKE_HPP

namespace dvfw {
namespace gen {
template <typename T, class base_generator>
class take : public base_generator {
   private:
    base_generator _gen;
    int _num;
    int _taken{0};

   public:
    take() = default;
    take(base_generator generator, int num) : _gen{generator}, _num{num} {}
    
    bool hasNext() {
        if(_taken >= _num) return false;
        return _gen.hasNext();
    }

    T next() {
        _taken++;
        return _gen.next();
    }
};
}  // namespace gen
}  // namespace dvfw

#endif  // GEN_TAKE_HPP
