/**
 * @file adjacent.hpp
 * @author Jonathan Boccara
 * @brief Adjacent generator class
 * @version 0.1
 * @date 2022-04-28
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef DFL_ADJACENT_HPP
#define DFL_ADJACENT_HPP

#include <dfl/impl/concepts.hpp>
#include <iterator>

namespace dfl::gen {
template <typename Range>
struct adjacent_range {
  Range const& range;
  explicit adjacent_range(Range const& range) : range(range) {}
};

/**
 * @brief Generator sending pairs of values
 *
 * EXAMPLE:
 * arr = {1,2,3,4};
 * auto adjacent(arr) -> [](auto v1, auto v2){ x + y }
 * = 3 5 7
 *
 * @tparam Range
 * @param range
 * @return auto
 */
template <typename Range>
auto adjacent(Range&& range) {
  return adjacent_range<std::decay_t<Range>>(FWD(range));
}

template <typename Range, typename Pipeline,
          detail::IsAPipeline<Pipeline> = true>
void operator>>=(adjacent_range<Range> rangesHolder, Pipeline&& pipeline) {
  auto& range = rangesHolder.range;

  using std::begin;
  using std::end;

  auto first = begin(range);
  auto second = begin(range);

  if (second != end(range)) {
    second++;
  }

  while (second != end(range)) {
    send(*first, *second, pipeline);

    first++;
    second++;
  }
}
}  // namespace dfl::gen

#endif /* DFL_ADJACENT_HPP */