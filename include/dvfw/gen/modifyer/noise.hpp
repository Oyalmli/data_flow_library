#ifndef GEN_MOD_NOISE_HPP
#define GEN_MOD_NOISE_HPP

namespace dvfw {
namespace gen {
template <typename T, class Gen>
class noise : public base_generator<T> {
   private:
    Gen _gen;
    T _noise;

   public:
    noise() = default;
    noise(T noise, Gen generator, int seed = time(0)) : _gen{generator}, _noise{noise} {
        srand(static_cast<unsigned>(seed));
    }

    double r() {
        return rand() / static_cast<double>(RAND_MAX);
    }

    bool hasNext() {
        return _gen.hasNext();
    }

    T next() {
        T offset = -_noise + (r() * 2 * _noise);
        return _gen.next() + offset;
    }
};
}  // namespace gen
}  // namespace dvfw

#endif  // GEN_MOD_NOISE_HPP
