/**
 * @file repeat.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Repeat generator modifyier class
 * @version 0.1
 * @date 2022-04-28
 *
 * @copyright Copyright (c) 2022
 * @example mod/repeat.cpp
 */
#ifndef GEN_MOD_REPEAT_HPP
#define GEN_MOD_REPEAT_HPP

namespace dfl::mod {
template <class Gen>
class repeat : public gen::base_generator<typename Gen::value_type> {
  using T = typename Gen::value_type;

 private:
  Gen _gen_init;
  Gen _gen;

 public:
  T _curr = _gen.curr();

  repeat(Gen generator) : _gen_init{generator}, _gen{generator} {}

  bool hasNext() const { return true; }
  T curr() const { return _curr; }

  void next() {
    _gen.next();
    if (!_gen.hasNext()) {
      _gen = _gen_init;
    }
    _curr = _gen.curr();
  }
  MAKE_ITER(repeat, T);
};
}  // namespace dfl::gen

#endif  // GEN_MOD_REPEAT_HPP
