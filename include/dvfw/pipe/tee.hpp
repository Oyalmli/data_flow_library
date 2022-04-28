/**
 * @file tee.hpp
 * @author Jonathan Boccara
 * @brief Tee pipeline class
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DVFW_TEE_HPP
#define DVFW_TEE_HPP

namespace dvfw::pipe {
template <typename TeeBranch>
class tee_pipe : public dvfw_base {
   public:
    template <typename Value, typename TailPipeline>
    void onReceive(Value&& value, TailPipeline&& tailPipeline) {
        send(value, teeBranch_);
        send(FWD(value), tailPipeline);
    }

    explicit tee_pipe(TeeBranch teeBranch) : teeBranch_(teeBranch) {}

   private:
    TeeBranch teeBranch_;
};

template <typename TeeBranch>
tee_pipe<std::decay_t<TeeBranch>> tee(TeeBranch&& predicate) {
    return tee_pipe<std::decay_t<TeeBranch>>{predicate};
}
};  // namespace dvfw

#endif /* DVFW_TEE_HPP */