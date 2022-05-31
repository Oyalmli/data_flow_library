#include "dfl/dfl.hpp"

using namespace dfl;
int main (){
    auto range_gen = gen::range(100);

    range_gen >>= sink::hole();
}

/* ./hole
*/