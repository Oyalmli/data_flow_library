#ifndef PRINT_HPP
#define PRINT_HPP

#include <string>

#include "dvfw/base.hpp"
#include "writer/writer.hpp"

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
    explicit print_pipeline(char sep) : _writer(sep, stdout) {}

   private:
    Writer _writer;
};

template <typename Sep>
print_pipeline<Sep> print(Sep sep) {
    return print_pipeline(sep);
}

template <typename Sep>
print_pipeline<Sep> print(Sep sep, FILE* outStream) {
    return print_pipeline(sep, outStream);
}

}  // namespace sink
}  // namespace dvfw

#endif /* PRINT_HPP */