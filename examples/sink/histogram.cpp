#include "dfl/dfl.hpp"
#include <map>

using namespace dfl;
int main (){
    std::map<int, int> hist;
    mod::noise(5, 
    mod::take(100,
    gen::value(5)))
    >>= sink::histogram(hist);

	for (auto const [k,v] : hist) {
		printf("%d: %d\n", k, v);
	}
}

/*
1: 12
2: 9
3: 12
4: 7
5: 21
6: 12
7: 10
8: 9
9: 8
*/