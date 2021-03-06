/**
 * @file to_out_stream.hpp
 * @author Jonathan Boccara
 * @brief To out stream sink class
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022
 * @example sink/to_out_stream.cpp
 */
#ifndef TO_OUT_STREAM_HPP
#define TO_OUT_STREAM_HPP

#include <functional>

namespace dfl::sink {
template <typename OutStream>
class to_out_stream_pipeline : public pipeline_base<to_out_stream_pipeline<OutStream>> {
   public:
    template <typename T>
    void onReceive(T&& value) {
        outStream_.get() << FWD(value);
    }

    explicit to_out_stream_pipeline(OutStream& outStream) : outStream_(outStream) {}

   private:
    std::reference_wrapper<OutStream> outStream_;
};

template <typename OutStream>
to_out_stream_pipeline<OutStream> to_out_stream(OutStream& outStream) {
    return to_out_stream_pipeline<OutStream>(outStream);
}
}  // namespace dfl::sink

#endif /* TO_OUT_STREAM_HPP */