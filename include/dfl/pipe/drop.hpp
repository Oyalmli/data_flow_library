/**
 * @file drop.hpp
 * @author Jonathan Boccara
 * @brief Drop generator class
 * @version 0.1
 * @date 2022-04-27
 * 
 * @copyright Copyright (c) 2022
 * @example pipe/drop.cpp
 */
#ifndef DFL_DROP_HPP
#define DFL_DROP_HPP

namespace dfl {
namespace pipe {
class drop : public dfl_base {
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
}  // namespace dfl

#endif /* PIPES_DROP_HPP */