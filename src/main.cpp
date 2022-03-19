#include <deque>
#include <iostream>
#include <vector>
#include <numeric>
#include <string>
#include <chrono>

#include "dvfw/dvfw.hpp"

int main() {
    //221ms
    auto generator = dvfw::gen::range(1, 1000000);
    generator >>= dvfw::for_each([](int i){ printf("hello: %d\n", i); });

    //207ms
    for (int i = 0; i < 1000000; i++) {
        printf("hello: %d\n", i);
    }
}

