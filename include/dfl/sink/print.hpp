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

namespace dfl::sink {

template <typename Sep>
class print : public pipeline_base<print<Sep>> {
    using OutWriter = Writer<128>;
   public:
    template <typename T>
    void onReceive(T&& value) {
        (*_writer) < value < _sep;
        _writer->flush();
    }

    print(Sep sep, FILE* fp=stdout) : _sep{sep} {
        _writer = new OutWriter(fp);
    }

   private:
    OutWriter* _writer;
    Sep _sep;
};
}  // namespace dfl::sink

#endif /* PRINT_HPP */