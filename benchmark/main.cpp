#include <iostream>
#include "dfl/dfl.hpp"

using namespace dfl; 
int main() {
	gen::range(0,10,1)
	>>= pipe::tap(_print_(_addValue(10)))
	>>= sink::printf("%d\n");
}