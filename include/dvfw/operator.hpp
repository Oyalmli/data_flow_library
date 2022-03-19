#ifndef OPERATOR_HPP
#define OPERATOR_HPP

#include <type_traits>

#include "dvfw/impl/concepts.hpp"
#include "dvfw/impl/pipes_assembly.hpp"

namespace dvfw {

// val >>= pipeline
template <
    typename Val,
    typename Pipeline,
    detail::IsAPipeline<Pipeline> = true>
std::enable_if_t<std::is_arithmetic_v<Val>>
operator>>=(Val& val, Pipeline&& pipeline) {
    dvfw::send(val, pipeline);
}

// range >>= pipeline (rvalue ranges)
template <
    typename Range,
    typename Pipeline,
    detail::IsARange<Range> = true,
    detail::IsAPipeline<Pipeline> = true>
std::enable_if_t<!std::is_lvalue_reference_v<Range>>
operator>>=(Range&& range, Pipeline&& pipeline) {
    std::copy(
        std::make_move_iterator(std::begin(range)),
        std::make_move_iterator(std::end(range)),
        pipeline);
}

// range >>= pipeline (lvalue ranges)
template <
    typename Range,
    typename Pipeline,
    detail::IsARange<Range> = true,
    detail::IsAPipeline<Pipeline> = true>
std::enable_if_t<std::is_lvalue_reference_v<Range>>
operator>>=(Range&& range, Pipeline&& pipeline) {
    std::copy(
        std::begin(range),
        std::end(range),
        pipeline);
}

// pipe >>= pipe
template <
    typename Pipe1,
    typename Pipe2,
    detail::IsAPipe<Pipe1> = true,
    detail::IsAPipe<Pipe2> = true>
auto operator>>=(Pipe1&& pipe1, Pipe2&& pipe2) {
    return detail::CompositePipe<std::decay_t<Pipe1>, std::decay_t<Pipe2>>(FWD(pipe1), FWD(pipe2));
}

// pipe >>= pipeline
template <
    typename Pipe,
    typename Pipeline,
    detail::IsAPipe<Pipe> = true,
    detail::IsAPipeline<Pipeline> = true>
auto operator>>=(Pipe&& pipe, Pipeline&& pipeline) {
    return make_generic_pipeline(pipe, pipeline);
}

}  // namespace dvfw

#endif /* OPERATOR_HPP */