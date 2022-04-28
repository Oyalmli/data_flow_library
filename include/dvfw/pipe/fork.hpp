/**
 * @file fork.hpp
 * @author Jonathan Boccara
 * @brief Fork pipeline class
 * @version 0.1
 * @date 2022-04-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DVFW_FORK_HPP
#define DVFW_FORK_HPP

#include "dvfw/helpers/meta.hpp"

namespace dvfw {
namespace pipe {
template <typename... TailPipelines>
class fork_pipeline : public pipeline_base<fork_pipeline<TailPipelines...>> {
   public:
    template <typename T>
    void onReceive(T&& value) {
        detail::for_each(tailPipelines_, [&value](auto&& tailPipeline) { send(FWD(value), tailPipeline); });
    }

    /**
     * @brief Forwards the same value to all pipelines defined in it
     * 
     * @param tailPipelines 
     */
    explicit fork_pipeline(TailPipelines const&... tailPipelines) : tailPipelines_(tailPipelines...) {}

   private:
    std::tuple<TailPipelines...> tailPipelines_;
};

template <typename... TailPipelines>
fork_pipeline<TailPipelines...> fork(TailPipelines const&... tailPipelines) {
    return fork_pipeline<TailPipelines...>(tailPipelines...);
}
}  // namespace pipe
}  // namespace dvfw

#endif /* DVFW_FORK_HPP */