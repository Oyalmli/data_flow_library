#ifndef DVFW_SET_STATE_HPP
#define DVFW_SET_STATE_HPP

namespace dvfw {
namespace pipe {
template <typename Function, typename State>
class set_state_pipe : public dvfw_base {
   public:
    template <typename... Values, typename TailPipeline>
    void onReceive(Values&&... values, TailPipeline&& tailPipeline) {
        function_(values..., state_);
        send(FWD(values)..., tailPipeline);
    }

    explicit set_state_pipe(Function function, State state) : function_(function), state_(state) {}

   private:
    Function function_;
    State state_;
};

template <typename Function, typename State>
set_state_pipe<Function, State> set_state(Function&& function, State&& state) {
    return set_state_pipe<Function, State>{function, state};
}
}  // namespace pipe
}  // namespace dvfw

#endif /* DVFW_SET_STATE_HPP */