#ifndef DVFW_OPTIONAL_HPP
#define DVFW_OPTIONAL_HPP

#include <optional>

namespace dvfw::detail {
using nullopt_t = std::nullopt_t;
static const nullopt_t nullopt = std::nullopt;

template <typename T>
using optional = std::optional<T>;


}  // namespace dvfw::detail

#endif /* DVFW_OPTIONAL_HPP */