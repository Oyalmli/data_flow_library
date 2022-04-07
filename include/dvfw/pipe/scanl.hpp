#ifndef DVFW_SCANL_HPP
#define DVFW_SCANL_HPP

namespace dvfw {
namespace pipe {
template <typename Function, typename State>
class scanl_pipe : public dvfw_base {
   public:
    template <typename... Values, typename TailPipeline>
    void onReceive(Values&&... values, TailPipeline&& tailPipeline) {
        state_ = function_(state_, values...);
        send(FWD(state_), tailPipeline);
    }

    explicit scanl_pipe(Function function, State initState) : function_(function), state_(initState) {}

   private:
    Function function_;
    State state_;
};

template <typename Function, typename State>
scanl_pipe<Function, State> scanl(Function&& function, State initState) {
    return scanl_pipe<Function, State>{function, initState};
}
}  // namespace pipe
}  // namespace dvfw

#endif /* DVFW_SCANL_HPP */