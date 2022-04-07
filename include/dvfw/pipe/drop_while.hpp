#ifndef DVFW_DROP_WHILE_HPP
#define DVFW_DROP_WHILE_HPP

#include "dvfw/base.hpp"
#include "dvfw/helpers/FWD.hpp"
#include "dvfw/helpers/assignable.hpp"

namespace dvfw {
namespace pipe {
template <typename Predicate>
class drop_while_pipe : public dvfw_base {
   public:
    template <typename... Values, typename TailPipeline>
    void onReceive(Values&&... values, TailPipeline&& tailPipeline) {
        if (!predicateHasBeenFalse_) {
            predicateHasBeenFalse_ = !predicate_(values...);
        }

        if (predicateHasBeenFalse_) {
            send(FWD(values)..., FWD(tailPipeline));
        }
    }

    explicit drop_while_pipe(Predicate predicate) : predicate_{predicate}, predicateHasBeenFalse_{false} {}

   private:
    detail::assignable<Predicate> predicate_;
    bool predicateHasBeenFalse_;
};

template <typename Predicate>
drop_while_pipe<Predicate> drop_while(Predicate&& predicate) {
    return drop_while_pipe<Predicate>(FWD(predicate));
}
}  // namespace pipe
}  // namespace dvfw

#endif /* DVFW_DROP_WHILE_HPP */