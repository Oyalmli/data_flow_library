#include <iostream>
#include <vector>
#include "dfl/dfl.hpp"

using namespace dfl; 
int main() {
	mod::take(10,
		gen::counter<int>()
	)
	>>= pipe::drop(5)
	>>= sink::printf("%d\n");
}