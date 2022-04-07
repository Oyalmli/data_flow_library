#ifndef DVFW_INTERSPERSE_HPP
#define DVFW_INTERSPERSE_HPP

#include "dvfw/base.hpp"
#include "dvfw/helpers/FWD.hpp"
#include "dvfw/send.hpp"

namespace dvfw {
namespace pipe {
template <typename Delimiter>
class intersperse_pipe : public pipe_base {
   public:
    template <typename T, typename TailPipeline>
    void onReceive(T&& value, TailPipeline& tailPipeline) {
        if (alreadyReceivedAValue_) {
            send(delimiter_, tailPipeline);
        }
        send(FWD(value), tailPipeline);
        alreadyReceivedAValue_ = true;
    }

    explicit intersperse_pipe(Delimiter delimiter) : delimiter_(std::move(delimiter)) {}

   private:
    Delimiter delimiter_;
    bool alreadyReceivedAValue_ = false;
};

template <typename Delimiter>
auto intersperse(Delimiter delimiter) {
    return intersperse_pipe<Delimiter>{delimiter};
}
}  // namespace pipe
}  // namespace dvfw

#endif /* DVFW_INTERSPERSE_HPP */