#include <string>
#include <vector>

#include "dvfw/dvfw.hpp"
#include "dvfw/generator/gen.hpp"

int main() {
    auto input_gen = dvfw::gen::file<int>(stdin);
    input_gen >>= dvfw::for_each([](int c){ printf("ye: %d\n", c); });
}
