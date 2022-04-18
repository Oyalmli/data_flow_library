#ifndef PRINT_HPP
#define PRINT_HPP

#include <string>
#include "../util/IO.hpp"

namespace dvfw {
namespace sink {

template <typename Sep>
class print_pipeline : public pipeline_base<print_pipeline<Sep>> {
   public:
    template <typename T>
    void onReceive(T&& value) {
        _writer.write(std::to_string(value));
    }

    explicit print_pipeline(Sep sep, FILE* outStream) : _writer(sep, outStream) {}
    

   private:
    Writer<128> _writer;
};

template <typename Sep>
print_pipeline<Sep> print(Sep sep) {
    return print_pipeline(sep, stdout);
}

template <typename Sep>
print_pipeline<Sep> print(Sep sep, FILE* outStream) {
    return print_pipeline(sep, outStream);
}

}  // namespace sink
}  // namespace dvfw

#endif /* PRINT_HPP */