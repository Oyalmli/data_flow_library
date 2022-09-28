/**
 * @file fork.hpp
 * @author Jonathan Boccara
 * @brief Fork pipeline class
 * @version 0.1
 * @date 2022-04-27
 * 
 * @copyright Copyright (c) 2022
 * @example rdir/fork.cpp
 */
#ifndef DFL_FORK_HPP
#define DFL_FORK_HPP

#include "dfl/helpers/meta.hpp"

namespace dfl::rdir {
template <typename... TailPipelines>
class fork_pipeline : public pipeline_base<fork_pipeline<TailPipelines...>> {
   public:
    template <typename... T>
    void onReceive(T&&... values) {
        detail::for_each(tailPipelines_, [&values...](auto&& tailPipeline) { send(FWD(values)..., tailPipeline); });
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
}  // namespace dfl::pipe

#endif /* DFL_FORK_HPP */