/**
 * @file adjacent.hpp
 * @author Jonathan Boccara
 * @brief Adjacent generator class
 * @version 0.1
 * @date 2022-04-28
 *
 * @copyright Copyright (c) 2022
 * @example gen/adjacent.cpp
 */
#ifndef DFL_ADJACENT_HPP
#define DFL_ADJACENT_HPP

#include <dfl/impl/concepts.hpp>
#include <iterator>

namespace dfl::gen {
template <typename Range>
struct adjacent_range {
  const Range& range;
  explicit adjacent_range(Range const& range) : range(range) {}
};

/**
 * @brief Generator sending pairs of values
 *
 * @tparam Range
 * @param range
 * @return auto
 */
template <typename Range>
auto adjacent(Range&& range) {
  return adjacent_range<Range>(FWD(range));
}

template <typename Range, typename Pipeline,
          detail::IsAPipeline<Pipeline> = true>
void operator>>=(adjacent_range<Range> rangesHolder, Pipeline&& pipeline) {
  auto range = rangesHolder.range;
  auto it = range.begin();
  auto end = range.end();
  
  if (it == end){ return; }

  auto a = *it;
  if (it == end) return;
  ++it; auto b = *it;
  while (it != end) {
    send(a, b, pipeline);
    a = b;
    ++it; b = *it;
  }
}
}  // namespace dfl::gen

#endif /* DFL_ADJACENT_HPP */