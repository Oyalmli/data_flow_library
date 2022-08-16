#include "dfl/dfl.hpp"

using namespace dfl;

int main (){
    auto inf_gen
    =   mod::take(20,
        mod::repeat(
        mod::take(5,
        gen::range(100))));

    inf_gen  
    >>= sink::print<'\n'>(); 
}

/* ./repeat
0
1
2
3
4
0
1
2
3
4
0
1
2
3
4
0
1
2
3
4
*/
