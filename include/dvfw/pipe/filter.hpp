#ifndef DVFW_FILTER_HPP
#define DVFW_FILTER_HPP

#include "dvfw/base.hpp"
#include "dvfw/helpers/assignable.hpp"
#include "dvfw/operator.hpp"

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