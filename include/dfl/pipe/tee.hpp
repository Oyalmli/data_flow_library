/**
 * @file tee.hpp
 * @author Jonathan Boccara
 * @brief Tee pipeline class
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022
 * @example pipe/tee.cpp
 */
#ifndef DFL_TEE_HPP
#define DFL_TEE_HPP

namespace dfl::pipe {
template <typename TeeBranch>
class tee_pipe : public dfl_base {
   public:
    template <typename... Values, typename TailPipeline>
    void onReceive(Values&&... values, TailPipeline&& tailPipeline) {
        send(values..., teeBranch_);
        send(FWD(values)..., tailPipeline);
    }

    explicit tee_pipe(TeeBranch teeBranch) : teeBranch_(teeBranch) {}

   private:
    TeeBranch teeBranch_;
};

template <typename TeeBranch>
tee_pipe<std::decay_t<TeeBranch>> tee(TeeBranch&& predicate) {
    return tee_pipe<std::decay_t<TeeBranch>>{predicate};
}
}  // namespace dfl

#endif /* DFL_TEE_HPP */