#ifndef DFL_CONCEPTS_HPP
#define DFL_CONCEPTS_HPP

#include <type_traits>

#include "dfl/impl/base.hpp"
#include "dfl/helpers/detect.hpp"

namespace dfl {
namespace detail {
namespace impl {
// definition of range

namespace adl {
using std::begin;
using std::end;
template <typename T>
using begin_expression = decltype(begin(std::declval<T&>()));
template <typename T>
using end_expression = decltype(end(std::declval<T&>()));
}  // namespace adl

template <typename Range>
constexpr bool range_expression_detected = detail::is_detected<adl::begin_expression, Range>&& detail::is_detected<adl::end_expression, Range>;

template <typename Range>
using IsARange = std::enable_if_t<range_expression_detected<Range>, bool>;

// definition of pipe

template <typename Pipe>
using IsAPipe = std::enable_if_t<std::is_base_of<dfl_base, Pipe>::value, bool>;

// definition of pipeline

template <typename Pipeline>
using IsAPipeline = std::enable_if_t<std::is_base_of<pipeline_base<Pipeline>, Pipeline>::value, bool>;
}  // namespace impl

template <typename Range>
using IsARange = impl::IsARange<std::remove_reference_t<Range>>;

template <typename Pipe>
using IsAPipe = impl::IsAPipe<std::remove_reference_t<Pipe>>;

template <typename Pipeline>
using IsAPipeline = impl::IsAPipeline<std::remove_reference_t<Pipeline>>;

}  // namespace detail
}  // namespace dfl

#endif /* DFL_CONCEPTS_HPP */