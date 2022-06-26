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

#define MAKE_ITER(CLASS, TP)                                 \
  const CLASS& begin() const { return *this; }               \
  const CLASS& end() const { return *this; }                 \
  bool operator!=(const CLASS&) const { return hasNext(); }  \
  bool operator==(const CLASS&) const { return !hasNext(); } \
  CLASS& operator++() {                                      \
    next();                                                  \
    return *this;                                            \
  }                                                          \
  TP operator*() const { return curr(); }

namespace dfl::gen {
template <typename Gen, typename T>
class GenIterator
    : public std::iterator<std::input_iterator_tag, T, bool, T*, T&> {
  Gen const* _gen;

 public:
  GenIterator(Gen const* gen) : _gen{gen} {};

  void operator++() { _gen->next(); }
  bool operator!=(const GenIterator&) const { return _gen->hasNext(); }
  bool operator==(const GenIterator&) const { return !(_gen->hasNext()); }
  T operator*() const { return _gen->curr(); }
};

template <typename T>
struct base_generator {
  struct iterator {
    typedef T                        value_type;
    typedef bool                     difference_type;
    typedef T*                       pointer;
    typedef T&                       reference;
    typedef std::input_iterator_tag  iterator_category;
  };

  using iterator_category = std::input_iterator_tag;
  using difference_type   = bool;
  using value_type        = T;
  using pointer           = T*;
  using reference         = T&;

  bool hasNext() const;
  T curr() const;
  void next();
};
}  // namespace dfl::gen

#endif /* DFL_GENERATOR_HPP */