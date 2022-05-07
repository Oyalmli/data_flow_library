#include <string>
#include <vector>

#include "../../catch.hpp"
#include "dvfw/dvfw.hpp"

using namespace dvfw;

const std::string prefix = "[NOISE]: ";

TEST_CASE(prefix + "Noisy range is not equal to range") {
    /*
  bool equal = false;
  /// auto noisy_range = gen::noise(10, gen::range(5), 123);
  auto noisy_range = gen::range(5);
  auto range = gen::range(5);

  noisy_range.begin();
  auto mux_range = gen::mux(noisy_range, range);
  mux_range >>=
      sink::for_each([&equal](auto a, auto b) { equal = equal || a == b; });
  REQUIRE(!equal);
  */
}
