/**
 * @file mux.hpp
 * @author Jonathan Boccara
 * @brief Mux generator class
 * @version 0.1
 * @date 2022-04-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DVFW_MUX_HPP
#define DVFW_MUX_HPP

#include <tuple>
#include <type_traits>

#include "dvfw/impl/concepts.hpp"

namespace dvfw {
namespace gen {

template <typename... Ranges>
struct muxer {
    std::tuple<Ranges const&...> inputs;
    explicit muxer(Ranges const&... inputs) : inputs(inputs...) {}
};

/**
 * @brief Creates conjoined tuples from the ranges supplied
 * 
 * @tparam Ranges 
 * @param ranges 
 * @return auto 
 */
template <typename... Ranges>
auto mux(Ranges&&... ranges) {
    static_assert(sizeof...(Ranges) > 0, "There should be at least one range in mux.");
    return muxer<std::decay_t<Ranges>...>(FWD(ranges)...);
}

}  // namespace gen

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

/**
 * @brief Connects muxer of ranges to a pipeline
 * 
 * @tparam Ranges 
 * @tparam Pipeline 
 * @param inputsMuxer 
 * @param pipeline 
 */
template <typename... Ranges, typename Pipeline, detail::IsAPipeline<Pipeline> = true>
void operator>>=(gen::muxer<Ranges...> inputsMuxer, Pipeline&& pipeline) {
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