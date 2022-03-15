#ifndef PUSH_BACK_HPP
#define PUSH_BACK_HPP

#include "dvfw/base.hpp"
#include "dvfw/helpers/FWD.hpp"

#include <functional>

namespace dvfw
{
    template<typename Container>
    class push_back_pipeline : public pipeline_base<push_back_pipeline<Container>>
    {
    public:
        template<typename T>
        void onReceive(T&& value)
        {
            container_.get().push_back(FWD(value));
        }
        
        explicit push_back_pipeline(Container& container) : container_(container) {}
        
    private:
        std::reference_wrapper<Container> container_;
    };
    
    template<typename Container>
    push_back_pipeline<Container> push_back(Container& container)
    {
        return push_back_pipeline<Container>(container);
    }
}

#endif /* PUSH_BACK_HPP */