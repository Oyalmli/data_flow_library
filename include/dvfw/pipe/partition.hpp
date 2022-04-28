/**
 * @file partition.hpp
 * @author Jonathan Boccara
 * @brief Partition pipeline class
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DVFW_PARTITION_HPP
#define DVFW_PARTITION_HPP

namespace dvfw::pipe {
template <typename OutputPipeTrue, typename OutputPipeFalse, typename Predicate>
class partition_pipe : public pipeline_base<partition_pipe<OutputPipeTrue, OutputPipeFalse, Predicate>> {
   public:
    template <typename... Ts>
    void onReceive(Ts&&... values) {
        if (predicate_(values...)) {
            send(FWD(values)..., outputPipeTrue_);
        } else {
            send(FWD(values)..., outputPipeFalse_);
        }
    }

    explicit partition_pipe(OutputPipeTrue iteratorTrue, OutputPipeFalse iteratorFalse, Predicate predicate) : outputPipeTrue_(iteratorTrue), outputPipeFalse_(iteratorFalse), predicate_(predicate) {}

   private:
    OutputPipeTrue outputPipeTrue_;
    OutputPipeFalse outputPipeFalse_;
    detail::assignable<Predicate> predicate_;
};

/**
 * @brief Given a predicate function a value will be sent to the first pipleine if true the other if not
 * 
 * @tparam Predicate 
 * @tparam OutputPipeTrue 
 * @tparam OutputPipeFalse 
 * @param predicate 
 * @param outputPipeTrue 
 * @param outputPipeFalse 
 * @return partition_pipe<OutputPipeTrue, OutputPipeFalse, Predicate> 
 */
template <typename Predicate, typename OutputPipeTrue, typename OutputPipeFalse>
partition_pipe<OutputPipeTrue, OutputPipeFalse, Predicate> partition(Predicate predicate, OutputPipeTrue&& outputPipeTrue, OutputPipeFalse&& outputPipeFalse) {
    return partition_pipe<OutputPipeTrue, OutputPipeFalse, Predicate>(FWD(outputPipeTrue), FWD(outputPipeFalse), predicate);
}
};  // namespace dvfw::pipe

#endif /* DVFW_PARTITION_HPP */