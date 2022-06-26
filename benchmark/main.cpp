#include <iostream>
#include <thread>
#include <chrono>

#include "InfInt.hpp"
#include "dfl/dfl.hpp"

using namespace dfl;

class fibonacci : public gen::base_generator<InfInt> {
    InfInt _curr{0}, _next{1};
    public:
    fibonacci() {}
    bool hasNext() const { return true; }
    InfInt curr() const { return _curr; }
    void next() {
        InfInt temp = _next;
        _next += _curr;
        _curr = temp;
    }
    MAKE_ITER(fibonacci, InfInt);
};

int main(){
  fibonacci()
  >>= pipe::intersperse("\n")
  >>= sink::to_out_stream(std::cout);
}
