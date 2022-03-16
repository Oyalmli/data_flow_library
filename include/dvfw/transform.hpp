#ifndef DVFW_TRANSFORM_HPP
#define DVFW_TRANSFORM_HPP

#include <type_traits>

#include "dvfw/base.hpp"
#include "dvfw/helpers/FWD.hpp"
#include "dvfw/helpers/assignable.hpp"
#include "dvfw/helpers/invoke.hpp"

namespace dvfw {
template <typename Function>
class transform_pipe : public dvfw_base {
   public:
    template <typename... Values, typename TailPipeline>
    void onReceive(Values&&... values, TailPipeline&& tailPipeline) {
        send(detail::invoke(function_.get(), FWD(values)...), tailPipeline);
    }

    explicit transform_pipe(Function function) : function_(function) {}

   private:
    detail::assignable<Function> function_;
};

template <typename Function>
transform_pipe<Function> transform(Function&& function) {
    return transform_pipe<Function>{function};
}

}  // namespace dvfw

#endif /* DVFW_TRANSFORM_HPP */