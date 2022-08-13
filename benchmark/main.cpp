#include <iostream>
#include "dfl/dfl.hpp"

using namespace dfl; 
int main() {
	gen::range(0,10,1)
	>>= sink::print();
}