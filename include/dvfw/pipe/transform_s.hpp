#ifndef DVFW_TRANSFORM_S_HPP
#define DVFW_TRANSFORM_S_HPP

#include <type_traits>

#include "dvfw/base.hpp"
#include "dvfw/helpers/FWD.hpp"
#include "dvfw/helpers/assignable.hpp"
#include "dvfw/helpers/invoke.hpp"

namespace dvfw {
namespace pipe {
template <typename Function, typename State>
class transform_s_pipe : public dvfw_base {
   public:
    template <typename... Values, typename TailPipeline>
    void onReceive(Values&&... values, TailPipeline&& tailPipeline) {
        send(FWD(function_(values..., state_)), tailPipeline);
    }

    explicit transform_s_pipe(Function function, State state) : function_(function), state_(state) {}

   private:
    Function function_;
    State state_;
};

template <typename Function, typename State>
transform_s_pipe<Function, State> transform_s(Function&& function, State&& state) {
    return transform_s_pipe<Function, State>{function, state};
}
}  // namespace pipe
}  // namespace dvfw

#endif /* DVFW_TRANSFORM_S_HPP */