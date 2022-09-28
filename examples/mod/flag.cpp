#include "dfl/dfl.hpp"

using namespace dfl;

int main (){
    bool flag = true;
    mod::flag(flag, gen::counter<int>())
    >>= pipe::tap([&](auto i){ if (i >= 10) flag = false; })
    >>= sink::print<'\n'>();
}

/*
1
2
3
4
5
6
7
8
9
10
*/