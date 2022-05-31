/**
 * @file take.hpp
 * @author Jonathan Boccara
 * @brief Take pipeline class
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022
 * @example pipe/take.cpp
 */
#ifndef DFL_TAKE_HPP
#define DFL_TAKE_HPP

namespace dfl::pipe {
class take : public dfl_base {
   public:
    template <typename... Values, typename TailPipeline>
    void onReceive(Values&&... values, TailPipeline&& tailPipeline) {
        if (nbTaken_ < nbToTake_) {
            send(FWD(values)..., tailPipeline);
            ++nbTaken_;
        }
    }
    /**
     * @brief Takes N values from e range, drops the rest
     * 
     * @param nbToTake 
     */
    explicit take(std::size_t nbToTake) : nbToTake_{nbToTake}, nbTaken_{0} {}

   private:
    std::size_t nbToTake_;
    std::size_t nbTaken_;
};
}  // namespace dfl::pipe

#endif /* PIPES_TAKE_HPP */