#ifndef GEN_MOD_NOISE_HPP
#define GEN_MOD_NOISE_HPP

namespace dvfw {
namespace gen {
template <class base_generator, typename T>
class noise : public base_generator {
   private:
    base_generator _gen;
    T _noise;

   public:
    noise() = default;
    noise(base_generator generator, T noise, int seed = time(0)) : _gen{generator}, _noise{noise} {
        srand(static_cast<unsigned>(seed));
    }
    float r() {
        return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
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
