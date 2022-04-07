#include "dvfw/dvfw.hpp"

using namespace dvfw;
int main() {
    Writer w;
    auto range_gen = gen::range<int>(10000000);
    range_gen >>= sink::for_each([&w](int i){ w.write(std::to_string(i));});
    w.flush();
}
