/**
 * @file drop.hpp
 * @author Jonathan Boccara
 * @brief Drop generator class
 * @version 0.1
 * @date 2022-04-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DVFW_DROP_HPP
#define DVFW_DROP_HPP

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
}  // namespace pipe
}  // namespace dvfw

#endif /* PIPES_DROP_HPP */