#include <iostream>
#include "dfl/dfl.hpp"

using namespace dfl; 
int main() {
	auto accum = 0;

	gen::file<int64_t>(stdin)
	>>= pipe::drop(10)
	>>= sink::sum(accum);
	std::cerr << accum << '\n';
}