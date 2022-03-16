#ifndef DVFW_INVOKE_HPP
#define DVFW_INVOKE_HPP

#include <functional>
#include <type_traits>

namespace dvfw {
namespace detail {
template <typename Functor, typename... Args>
typename std::enable_if_t<
    std::is_member_pointer_v<typename std::decay_t<Functor>>,
    typename std::result_of_t<Functor && (Args && ...)>>
invoke(Functor&& f, Args&&... args) {
    return std::mem_fn(f)(std::forward<Args>(args)...);
}

template <typename Functor, typename... Args>
typename std::enable_if_t<
    !std::is_member_pointer_v<typename std::decay_t<Functor>>,
    typename std::result_of_t<Functor && (Args && ...)>>
invoke(Functor&& f, Args&&... args) {
    return std::forward<Functor>(f)(std::forward<Args>(args)...);
}
}  // namespace detail
}  // namespace dvfw

#endif /* DVFW_INVOKE_HPP */