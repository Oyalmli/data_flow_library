#ifndef DVFW_DROP_HPP
#define DVFW_DROP_HPP

#include "dvfw/base.hpp"
#include "dvfw/helpers/FWD.hpp"

namespace dvfw {
namespace pipe {
class drop : public dvfw_base {
   public:
    template <typename... Values, typename TailPipeline>
    void onReceive(Values&&... values, TailPipeline&& tailPipeline) {
        if (nbDropped_ >= nbToDrop_) {
            send(FWD(values)..., tailPipeline);
        } else {
            ++nbDropped_;
        }
    }

    explicit drop(std::size_t nbToDrop) : nbToDrop_{nbToDrop}, nbDropped_{0} {}

   private:
    std::size_t nbToDrop_;
    std::size_t nbDropped_;
};
}
}  // namespace dvfw

#endif /* PIPES_DROP_HPP */