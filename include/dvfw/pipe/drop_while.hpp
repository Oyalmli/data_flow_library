/**
 * @file drop_while.hpp
 * @author Jonathan Boccara
 * @brief Drop while pipeline class
 * @version 0.1
 * @date 2022-04-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DVFW_DROP_WHILE_HPP
#define DVFW_DROP_WHILE_HPP

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