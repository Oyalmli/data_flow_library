#ifndef DVFW_MUX_HPP
#define DVFW_MUX_HPP

#include <tuple>
#include <type_traits>

#include "dvfw/impl/concepts.hpp"

namespace dvfw {
namespace pipe {

template <typename... Ranges>
struct muxer {
    std::tuple<Ranges const&...> inputs;
    explicit muxer(Ranges const&... inputs) : inputs(inputs...) {}
};

template <typename... Ranges>
auto mux(Ranges&&... ranges) {
    static_assert(sizeof...(Ranges) > 0, "There should be at least one range in mux.");
    return muxer<std::decay_t<Ranges>...>(FWD(ranges)...);
}

}  // namespace pipe

namespace detail {
template <typename... Ts>
bool match_on_any(std::tuple<Ts...> const& tuple1, std::tuple<Ts...> const& tuple2) {
    auto matchOnAny = false;
    detail::for_each2(tuple1, tuple2, [&matchOnAny](auto&& element1, auto&& element2) {
        if (!matchOnAny && element1 == element2) {
            matchOnAny = true;
        }
    });
    return matchOnAny;
}

template <typename... Ts>
void increment(std::tuple<Ts...>& tuple) {
    for_each(tuple, [](auto&& element) { ++element; });
}
}  // namespace detail

template <typename... Ranges, typename Pipeline, detail::IsAPipeline<Pipeline> = true>
void operator>>=(pipe::muxer<Ranges...> inputsMuxer, Pipeline&& pipeline) {
    auto const beginIterators = detail::transform(inputsMuxer.inputs, [](auto&& range) { return begin(range); });
    auto const endIterators = detail::transform(inputsMuxer.inputs, [](auto&& range) { return end(range); });

    for (auto iterators = beginIterators;
         !detail::match_on_any(iterators, endIterators);
         detail::increment(iterators)) {
        sendTupleValues(detail::dereference(iterators), pipeline);
    }
}

}  // namespace dvfw

#endif /* PIPES_MUX_HPP */