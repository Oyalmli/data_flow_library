#include "dvfw/dvfw.hpp"

int main() {
    long long min_found = __LONG_LONG_MAX__;

    auto input_gen = dvfw::gen::file<long long>(stdin);

    auto pipeline 
    =   dvfw::drop(1)
    >>= dvfw::scanl([](long long curr, long long& acc){ return curr + acc; }, 0LL)
    >>= dvfw::set_state([](long long i, long long& min){ min = i < min ? i : min; }, min_found)
    >>= dvfw::hole();

    input_gen >>= pipeline;

    printf("result: %lld\n", std::max(0LL, -min_found));
}

