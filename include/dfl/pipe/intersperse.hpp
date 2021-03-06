/**
 * @file intersperse.hpp
 * @author Jonathan Boccara
 * @brief Intersperse pipeline class
 * @version 0.1
 * @date 2022-04-27
 * 
 * @copyright Copyright (c) 2022
 * @example pipe/intersperse.cpp
 */
#ifndef DFL_INTERSPERSE_HPP
#define DFL_INTERSPERSE_HPP

namespace dfl {
namespace pipe {
template <typename Delimiter>
class intersperse_pipe : public dfl_base {
   public:
    template <typename T, typename TailPipeline>
    void onReceive(T&& value, TailPipeline& tailPipeline) {
        if (alreadyReceivedAValue_) {
            send(delimiter_, tailPipeline);
        }
        send(FWD(value), tailPipeline);
        alreadyReceivedAValue_ = true;
    }

    explicit intersperse_pipe(Delimiter delimiter) : delimiter_(std::move(delimiter)) {}

   private:
    Delimiter delimiter_;
    bool alreadyReceivedAValue_ = false;
};
/**
 * @brief Places the delemiter value between each recieved value
 * 
 * @tparam Delimiter 
 * @param delimiter 
 * @return auto 
 */
template <typename Delimiter>
auto intersperse(Delimiter delimiter) {
    return intersperse_pipe<Delimiter>{delimiter};
}
}  // namespace pipe
}  // namespace dfl

#endif /* DFL_INTERSPERSE_HPP */