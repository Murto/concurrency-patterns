#include "parallel_normalize.hpp"

#include <iostream>
#include <vector>

int main() {
  constexpr double NUM_COUNT = 1000000;
  std::vector<double> nums;
  for (double i = 0; i < NUM_COUNT; ++i) {
    nums.push_back(i);
  }
  parallel_normalize(nums);
}
