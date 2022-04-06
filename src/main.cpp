#include "dvfw/dvfw.hpp"
#include "dvfw/generator/gen.hpp"

int main() {
    auto range_gen = dvfw::gen::range<int>(1,10);

    range_gen >>= dvfw::printf("val: %d\n");
}
