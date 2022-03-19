#ifndef TO_OUT_STREAM_HPP
#define TO_OUT_STREAM_HPP

#include <functional>

#include "dvfw/base.hpp"

namespace dvfw {

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

}  // namespace dvfw

#endif /* TO_OUT_STREAM_HPP */