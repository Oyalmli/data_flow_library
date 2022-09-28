#include "dfl/dfl.hpp"

using namespace dfl;

int main (){
    int curr;
    gen::range(10)
    >>= rdir::fork(
      pipe::transform([](int i){return i * 10;}) >>= pipe::set_var(curr) >>= sink::hole(),
      pipe::get_var(curr) >>= sink::printf("%d\n")
    );
}

/*
0 
10
20
30
40
50
60
70
80
90
*/