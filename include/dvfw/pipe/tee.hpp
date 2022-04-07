#ifndef DVFW_TEE_HPP
#define DVFW_TEE_HPP

#include <type_traits>

#include "dvfw/base.hpp"
#include "dvfw/helpers/FWD.hpp"

namespace dvfw {
namespace pipe {
template <typename TeeBranch>
class tee_pipe : public dvfw_base {
   public:
    template <typename Value, typename TailPipeline>
    void onReceive(Value&& value, TailPipeline&& tailPipeline) {
        send(value, teeBranch_);
        send(FWD(value), tailPipeline);
    }

    explicit tee_pipe(TeeBranch teeBranch) : teeBranch_(teeBranch) {}

   private:
    TeeBranch teeBranch_;
};

template <typename TeeBranch>
tee_pipe<std::decay_t<TeeBranch>> tee(TeeBranch&& predicate) {
    return tee_pipe<std::decay_t<TeeBranch>>{predicate};
}
}  // namespace pipe
}  // namespace dvfw

#endif /* DVFW_TEE_HPP */