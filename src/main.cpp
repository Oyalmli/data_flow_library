#include <iostream>
#include <iterator>
#include <vector>

#include "dvfw/dvfw.hpp"

using namespace dvfw;

template <typename _IO>
auto pp(_IO& io) { return [&io](int rhs) { io << rhs << '\n'; }; }

auto even = [](auto i) { return i % 2 == 0; };

auto add(int i) { return [=](int j) { return i + j; }; }

template<typename _IO, typename T>
class io_gen : public gen::base_generator<T> {
    private:
    _IO& _io;

    public:
    io_gen(_IO& io) : _io{io} {}

    bool hasNext() {
        return _io.reader.hasNext();
    }

    T next(){
        return _io.reader.template next<T>();
    }
};

int main() {
    using IO = IO<(1<<16), 32>;

    IO io;
    long long sum = 0;   
    auto generator = gen::It(io_gen<IO, long long>(io));
    auto pipeline = sink::for_each([&sum](auto i){ sum+=i; });
    generator >>= pipeline;

    io << sum << '\n';
    io.writer.flush();
}
