/**
 * @file take.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Take generator modifyier class
 * @version 0.1
 * @date 2022-04-28
 *
 * @copyright Copyright (c) 2022
 * @example mod/take.cpp
 */
#ifndef GEN_MOD_TAKE_HPP
#define GEN_MOD_TAKE_HPP

namespace dfl::mod {
template <class Gen>
class take : public gen::base_generator<typename Gen::value_type> {
  using T = typename Gen::value_type;
  //using iterator = GenIterator<take<Gen>, T>;

 private:
  Gen _gen;
  size_t _num;
  size_t _taken{0};
  T _curr = _gen.curr();

 public:
  take(size_t num, const Gen generator) : _gen{generator}, _num{num} {}

  bool hasNext() const { return _gen.hasNext() && (_taken < _num); }
  T curr() const { return _curr; }

  void next() {
    _taken++;
    _gen.next();
    _curr = _gen.curr();
  }
  
  MAKE_ITER(take, T);
};
}  // namespace dfl::gen

#endif  // GEN_MOD_TAKE_HPP
