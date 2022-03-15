#ifndef DVFW_TAKE_HPP
#define DVFW_TAKE_HPP

#include "dvfw/base.hpp"
#include "dvfw/helpers/FWD.hpp"

namespace dvfw
{
    class take : public dvfw_base
    {
    public:
        template<typename... Values, typename TailPipeline>
        void onReceive(Values&&... values, TailPipeline&& tailPipeline)
        {
            if (nbTaken_ < nbToTake_)
            {
                send(FWD(values)..., tailPipeline);
                ++nbTaken_;
            }
        }
        
        explicit take(std::size_t nbToTake) : nbToTake_{nbToTake}, nbTaken_{0} {}
        
    private:
        std::size_t nbToTake_;
        std::size_t nbTaken_;
    };
} // namespace pipes

#endif /* PIPES_TAKE_HPP */