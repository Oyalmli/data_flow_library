#ifndef DVFW_TAP_HPP
#define DVFW_TAP_HPP

#include <type_traits>

#include "dvfw/base.hpp"
#include "dvfw/helpers/FWD.hpp"
#include "dvfw/helpers/assignable.hpp"

namespace dvfw {
namespace pipe {
template <typename Function>
class tap_pipe : public dvfw_base {
   public:
    template <typename Value, typename TailPipeline>
    void onReceive(Value&& value, TailPipeline&& tailPipeline) {
        function_(FWD(value));
        send(FWD(value), tailPipeline);
    }

    template <typename Value>
    void onReceive(Value&& value) {
        function_(FWD(value));
    }

    explicit tap_pipe(Function function) : function_(function) {}

   private:
    detail::assignable<Function> function_;
};

template <typename Function>
tap_pipe<std::decay_t<Function>> tap(Function&& function) {
    return tap_pipe<std::decay_t<Function>>(FWD(function));
}
}  // namespace pipe
}  // namespace dvfw

#endif /* DVFW_TAP_HPP */