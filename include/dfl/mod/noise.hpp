/**
 * @file noise.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Noise generator modifyier class
 * @version 0.1
 * @date 2022-04-28
 *
 * @copyright Copyright (c) 2022
 * @example mod/noise.cpp
 */
#ifndef GEN_MOD_NOISE_HPP
#define GEN_MOD_NOISE_HPP

namespace dfl::mod {
template <class Gen>
class noise : public gen::base_generator<typename Gen::value_type> {
  using T = typename Gen::value_type;

 private:
  Gen _gen;
  T _noise;
  T _curr = _gen.curr();

  double r() { return rand() / static_cast<double>(RAND_MAX); }

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
  noise(T noise, Gen generator, int seed = time(0))
      : _gen{generator}, _noise{noise} {
    srand(static_cast<unsigned>(seed));
  }

  bool hasNext() const { return _gen.hasNext(); }
  T curr() const { return _curr; }
  void next() {
    T offset = -_noise + (r() * 2 * _noise);
    _gen.next();
    _curr = _gen.curr() + offset;
  }

  MAKE_ITER(noise, T);
};
}  // namespace dfl::gen

#endif  // GEN_MOD_NOISE_HPP
