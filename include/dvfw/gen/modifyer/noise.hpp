/**
 * @file noise.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Noise generator modifyier class
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef GEN_MOD_NOISE_HPP
#define GEN_MOD_NOISE_HPP

namespace dvfw::gen {
template <typename T, class Gen>
class noise : public base_generator<T> {
   private:
    Gen _gen;
    T _noise;

    double r() {
        return rand() / static_cast<double>(RAND_MAX);
    }

   public:
    /**
     * @brief Default noise constructor
     * @warning Do not use
     */
    noise() = default;
    /**
     * @brief Modifies the values supplied by the generator with a set noise range
     * 
     * @param noise 
     * @param generator 
     * @param seed 
     */
    noise(T noise, Gen generator, int seed = time(0)) : _gen{generator}, _noise{noise} {
        srand(static_cast<unsigned>(seed));
    }

    bool hasNext() {
        return _gen.hasNext();
    }

    T next() {
        T offset = -_noise + (r() * 2 * _noise);
        return _gen.next() + offset;
    }
};
}; // namespace dvfw::gen

#endif  // GEN_MOD_NOISE_HPP
