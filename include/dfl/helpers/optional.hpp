#ifndef DFL_OPTIONAL_HPP
#define DFL_OPTIONAL_HPP

#include <optional>

namespace dfl::detail {
using nullopt_t = std::nullopt_t;
static const nullopt_t nullopt = std::nullopt;

template <typename T>
using optional = std::optional<T>;


}  // namespace dfl::detail

#endif /* DFL_OPTIONAL_HPP */