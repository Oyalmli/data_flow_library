/**
 * @file print.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Print sink class
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022
 * @example sink/print.cpp
 */
#ifndef PRINT_HPP
#define PRINT_HPP

#include <string>
#include "../util/IO.hpp"

namespace dfl::sink {

template <char Sep = '\0'>
class print : public pipeline_base<print<Sep>> {
    using OutWriter = Writer<128>;
   public:
    template <typename T>
    constexpr void onReceive(T&& value) {
        if constexpr (Sep == '\0') {
            (*_writer) < value;
        } else {
            (*_writer) < value < Sep;
        }
        _writer->flush();
    }

    /**
     * @brief Prints the incoming value separated by the char template argument
     * 
     * @param fp 
     */
    print(FILE* fp=stdout) {
        _writer = new OutWriter(fp);
    }

   private:
    OutWriter* _writer;
};
}  // namespace dfl::sink

#endif /* PRINT_HPP */