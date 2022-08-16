#include "dfl/dfl.hpp"

using namespace dfl;

int main (){
    auto file_gen = gen::file<int>(stdin);
    file_gen >>= sink::print<'\n'>();
}

/* input.txt
1 2 3 4 5 6 7 8 9
*/

/* ./file < input.txt
1
2
3
4
5
6
7
8
9
*/