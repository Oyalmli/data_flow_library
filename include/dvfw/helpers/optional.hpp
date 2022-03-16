#ifndef DVFW_OPTIONAL_HPP
#define DVFW_OPTIONAL_HPP

#include <optional>

namespace dvfw {
namespace detail {
using nullopt_t = std::nullopt_t;
static const nullopt_t nullopt = std::nullopt;

template <typename T>
using optional = std::optional<T>;

}  // namespace detail
}  // namespace dvfw

#endif /* DVFW_OPTIONAL_HPP */