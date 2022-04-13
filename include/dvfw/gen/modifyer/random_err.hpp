#ifndef GEN_MOD_RANDOM_ERR_HPP
#define GEN_MOD_RANDOM_ERR_HPP

namespace dvfw {
namespace gen {
template <class Gen, typename T>
class random_err : public base_generator<T> {
    Gen _gen;
    float _chance;
    T _err;

   public:
    random_err(float chance, T err, Gen generator, int seed = time(0)) : _gen{generator}, _chance{chance}, _err{err} {
        srand(static_cast<unsigned>(seed));
    }

    float r() {
        return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    }

    bool hasNext() {
        return _gen.hasNext();
    }

    T next() {
        T curr = _gen.next();
        return (_chance > r()) ? _err : curr;
    }
};
}  // namespace gen
}  // namespace dvfw

#endif  // GEN_MOD_RANDOM_ERR_HPP
