#ifndef OPERATOR_HPP
#define OPERATOR_HPP

#include <iostream>
#include <type_traits>

#include "dfl/impl/concepts.hpp"
#include "dfl/impl/pipes_assembly.hpp"

namespace dfl {
// range >>= pipeline (rvalue ranges)

template <typename Range, typename Pipeline, detail::IsARange<Range> = true,
          detail::IsAPipeline<Pipeline> = true>
std::enable_if_t<!std::is_lvalue_reference<Range>::value> operator>>=(
    Range&& range, Pipeline&& pipeline) {
  for (const auto i : range) send(i, pipeline);
}

// range >>= pipeline (lvalue ranges)

template <typename Range, typename Pipeline, detail::IsARange<Range> = true,
          detail::IsAPipeline<Pipeline> = true>
std::enable_if_t<std::is_lvalue_reference<Range>::value> operator>>=(
    Range&& range, Pipeline&& pipeline) {
  for (const auto i : range) send(i, pipeline);
}

// pipe >>= pipe

template <typename Pipe1, typename Pipe2, detail::IsAPipe<Pipe1> = true,
          detail::IsAPipe<Pipe2> = true>
auto operator>>=(Pipe1&& pipe1, Pipe2&& pipe2) {
  return detail::CompositePipe<std::decay_t<Pipe1>, std::decay_t<Pipe2>>(
      FWD(pipe1), FWD(pipe2));
}

// pipe >>= pipeline

template <typename Pipe, typename Pipeline, detail::IsAPipe<Pipe> = true,
          detail::IsAPipeline<Pipeline> = true>
auto operator>>=(Pipe&& pipe, Pipeline&& pipeline) {
  return make_generic_pipeline(pipe, pipeline);
}

}  // namespace dfl

#endif /* OPERATOR_HPP */