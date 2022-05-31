/**
 * @file random_err.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Random Error generator modifyier class
 * @version 0.1
 * @date 2022-04-28
 *
 * @copyright Copyright (c) 2022
 * @example mod/random_err.cpp
 */
#ifndef GEN_MOD_RANDOM_ERR_HPP
#define GEN_MOD_RANDOM_ERR_HPP

namespace dfl::mod {
template <class Gen>
class random_err : public gen::base_generator<random_err<Gen>, typename Gen::value_type> {
  using T = typename Gen::value_type;

 private:
  Gen _gen;
  double _chance;
  T _err;
  T _curr = _gen.curr();

 public:
  /**
   * @brief Has a set chance to insert a set error value
   *
   * @param chance
   * @param err
   * @param generator
   * @param seed
   */
  random_err(double chance, T err, Gen generator, int seed = time(0))
      : _gen{generator}, _chance{chance}, _err{err} {
    srand(static_cast<unsigned>(seed));
  }
  IT(random_err<Gen>, T);

  double r() {
    return static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
  }

  bool hasNext() { return _gen.hasNext(); }

  T next() {
    T curr = _gen.next();
    _curr = (_chance > r()) ? _err : curr;
    return _curr;
  }

  T curr() { return _curr; }
};
}  // namespace dfl::gen

#endif  // GEN_MOD_RANDOM_ERR_HPP
