#include <string>
#include <vector>

#include "../../catch.hpp"
#include "dfl/dfl.hpp"

using namespace dfl;

const std::string prefix = "[NOISE]: ";

TEST_CASE(prefix + "Noisy range is not equal to range") {
  bool equal = true;
  auto noisy_range = mod::noise(10, gen::range(5), 123);
  auto range = gen::range(5);

  noisy_range.begin();
  auto mux_range = gen::mux(noisy_range, range);
  mux_range >>=
      sink::for_each([&equal](auto a, auto b) { equal &= a == b; });
  
  REQUIRE(!equal);
}
