/**
 * @file filter.hpp
 * @author Jonathan Boccara
 * @brief Filter pipeline class
 * @version 0.1
 * @date 2022-04-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DVFW_FILTER_HPP
#define DVFW_FILTER_HPP

namespace dvfw {
namespace pipe {
template <typename Predicate>
class filter_pipe : public dvfw_base {
   public:
    template <typename... Values, typename TailPipeline>
    void onReceive(Values&&... values, TailPipeline&& tailPipeline) {
        if (predicate_(values...)) {
            send(FWD(values)..., tailPipeline);
        }
    }

    explicit filter_pipe(Predicate predicate) : predicate_(predicate) {}

   private:
    detail::assignable<Predicate> predicate_;
};

template <typename Predicate>
auto filter(Predicate&& predicate) {
    return filter_pipe<std::decay_t<Predicate>>{predicate};
}
}  // namespace pipe
}  // namespace dvfw

#endif /* DVFW_FILTER_HPP */