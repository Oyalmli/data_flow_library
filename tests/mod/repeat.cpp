#include <string>
#include <vector>
#include <iostream>

#include "../catch.hpp"
#include "dfl/dfl.hpp"

using namespace dfl;

const std::string prefix = "[REPEAT]: ";

TEST_CASE(prefix + "Repeat repeats a range, can take from it") {
  auto repeat_range = mod::take(100, mod::repeat(gen::range(5)));
  std::vector<int> res;
  repeat_range >>= sink::push_back(res);
  REQUIRE(res.size() == 100);
}
