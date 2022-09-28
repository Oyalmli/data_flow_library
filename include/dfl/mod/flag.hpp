/**
 * @file flag.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Flag Modifier class
 * @version 0.1
 * @date 2022-04-28
 *
 * @copyright Copyright (c) 2022
 * @example mod/flag.cpp
 */
#ifndef GEN_FLAG_HPP
#define GEN_FLAG_HPP

namespace dfl::mod {
template <typename _flagTp, class Gen>
class flag_mod : public gen::base_generator<typename Gen::value_type> {
  using T = typename Gen::value_type;

 private:
  Gen _gen;
  _flagTp _flag;
  T _curr = _gen.curr();

 public:
  flag_mod(_flagTp flag, const Gen generator) : _gen{generator}, _flag(flag) {}

  bool hasNext() const { return _gen.hasNext() && _flag; }
  T curr() const { return _curr; }

  void next() {
    _gen.next();
    _curr = _gen.curr();
  }
  
  MAKE_ITER(flag_mod, T);
};

template<typename _flagTp, typename Gen>
flag_mod<_flagTp, Gen> flag(_flagTp&& continue_flag, const Gen generator) {
    return flag_mod<_flagTp, Gen>{continue_flag, generator};
}
}  // namespace dfl::gen

#endif  // GEN_MOD_TAKE_HPP
