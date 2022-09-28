#include <iostream>
#include "dfl/dfl.hpp"

using namespace dfl; 
int main() {
  auto Add15
  =   pipe::transform(_addValue(15));
  auto FilterEven
  =   pipe::filter(_even);
  auto Print
  =   sink::printf("Even: %d\n");

  gen::range(0,10,1)
  >>= Add15
  >>= FilterEven
  >>= Print; 
}