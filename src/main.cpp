#include "dvfw/dvfw.hpp"

using namespace dvfw;

int main() {
    auto range_gen = gen::take<double, gen::sine<double>>(gen::sine<double>(0.001, 1.0, 0.0), 1000);
    range_gen
    >>= pipe::transform([](double i){ return i + 1.0;})
    >>= sink::printf("%f\n");
}
