/**
 * @file print.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Print sink class
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef PRINT_HPP
#define PRINT_HPP

#include <string>
#include "../util/IO.hpp"

namespace dvfw::sink {

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
/**
 * @brief Prints the values recieved using the writer class
 * @see Writer
 * @tparam Sep 
 * @param sep 
 * @param outStream, default stdout
 * @return print_pipeline<Sep> 
 */
template <typename Sep>
print_pipeline<Sep> print(Sep sep, FILE* outStream = stdout) {
    return print_pipeline(sep, stdout);
}
};  // namespace dvfw::sink

#endif /* PRINT_HPP */