/**
 * @file take.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Take generator modifyier class
 * @version 0.1
 * @date 2022-04-28
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef GEN_MOD_TAKE_HPP
#define GEN_MOD_TAKE_HPP

namespace dfl::gen {
template <class Gen>
class take : public base_generator<take<Gen>, typename Gen::value_type> {
  using T = typename Gen::value_type;
  //using iterator = GenIterator<take<Gen>, T>;

 private:
  Gen _gen;
  size_t _num;
  size_t _taken{0};
  T _curr = _gen.curr();

 public:
  take(size_t num, Gen generator) : _gen{generator}, _num{num} {}
  IT(take<Gen>, T);

  /**
   * @brief Return true of the generator has more values, and not enough values
   * have been taken
   *
   * @return bool
   */
  bool hasNext() { return _gen.hasNext() && (_taken < _num); }

  T next() {
    _taken++;
    _gen.next();
    _curr = _gen.curr();
    return _curr;
  }

  T curr() { return _curr; }

  //iterator begin() { return iterator(this); }
  //iterator end() { return iterator(nullptr); }
};
}  // namespace dfl::gen

#endif  // GEN_MOD_TAKE_HPP
