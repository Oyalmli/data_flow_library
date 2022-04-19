#include <iostream>
#include <iterator>
#include <vector>

#include "dvfw/dvfw.hpp"

using namespace dvfw;

template <typename _IO>
auto pp(_IO& io) { return [&io](int rhs) { io << rhs << '\n'; }; }

//auto even = [](auto i) { return i % 2 == 0; };

auto add(int i) { return [=](int j) { return i + j; }; }

int main() {
    IO io;

    auto generator = gen::take(10, gen::value(10));

    for (auto i : generator) {
        io << i << '\n';
    }

    io.writer.flush();
}
