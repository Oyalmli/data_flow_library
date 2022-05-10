/**
 * @file base_generator.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief abstract base class for the generators
 * @version 0.1
 * @date 2022-04-27
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef DFL_GENERATOR_HPP
#define DFL_GENERATOR_HPP

#include <iterator>
#include <thread>

#define IT(ITER_CLASS, TYPE)                                                  \
  typename dfl::gen::base_generator<ITER_CLASS, TYPE>::iterator begin() {    \
    return                                                                    \
        typename dfl::gen::base_generator<ITER_CLASS, TYPE>::iterator(this); \
  };                                                                          \
  typename dfl::gen::base_generator<ITER_CLASS, TYPE>::iterator end() {      \
    return typename dfl::gen::base_generator<ITER_CLASS, TYPE>::iterator(    \
        nullptr);                                                             \
  };

namespace dfl::gen {
template <typename Gen, typename T>
class GenIterator
    : public std::iterator<std::input_iterator_tag, T, bool, T*, T&> {
  Gen* _gen;

 public:
  GenIterator(Gen* gen) : _gen{gen} {};

  GenIterator& operator++() {
    _gen->next();
    return *this;
  }
  bool operator!=(GenIterator& other) { return _gen->hasNext(); }
  bool operator==(GenIterator& other) { return !(_gen->hasNext()); }
  T operator*() { return _gen->curr(); }
};

template <class Gen, typename T>
class base_generator {
 public:
  using iterator = GenIterator<Gen, T>;
  using value_type = T;
  bool hasNext();
  T curr();
  T next();
  virtual iterator begin() = 0;
  virtual iterator end() = 0;

  template <typename Pipeline>
  void operator>>=(Pipeline&& pipeline) {
    while (hasNext()) {
      send(next(), pipeline);
    }
  }

  constexpr void wait(int delay) {
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
  }
};
}  // namespace dfl::gen

#endif /* DFL_GENERATOR_HPP */