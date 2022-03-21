#include <string>
#include <vector>

#include "dvfw/dvfw.hpp"
#include "dvfw/generator/gen.hpp"

int main() {
    std::vector<std::string> res;
    auto input_gen = dvfw::gen::file<std::string>(stdin);
    input_gen >>= dvfw::for_each([](std::string str){ printf("%s\n", str.c_str()); });
}
