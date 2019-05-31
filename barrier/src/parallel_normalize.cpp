#include "Barrier.hpp"
#include "parallel_normalize.hpp"

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

double sum_range(const std::vector<double>& nums, unsigned int begin, unsigned int end) {
  double sum = 0;
  for (auto i = begin; i < end; ++i) {
    sum += nums[i];
  }
  return sum;
}

void normalize_range(std::vector<double>& nums, unsigned int begin, unsigned int end, double mean) {
  for (auto i = begin; i < end; ++i) {
    nums[i] /= mean;
  }
}

std::vector<double> parallel_normalize(std::vector<double> nums) {
  constexpr unsigned int THREAD_COUNT = 4;
  double mean = 0;
  std::mutex own_mean;
  Barrier<THREAD_COUNT> barrier;
  std::vector<std::thread> threads;
  for (unsigned int i = 0; i < THREAD_COUNT; ++i) {
    auto begin = i * (nums.size() / THREAD_COUNT);
    auto end = begin + (nums.size() / THREAD_COUNT);
    threads.emplace_back([&nums, &mean, &own_mean, &barrier, i, begin, end] {
      auto sum = sum_range(nums, begin, end);
      {
        std::lock_guard<std::mutex> lock{own_mean};
        mean += sum / nums.size();
      }
      barrier.enter();
      normalize_range(nums, begin, end, mean);
    });
  }
  for (auto& thread : threads) {
    thread.join();
  }
  std::cout << "Mean: " << mean << '\n';
  return nums;
}
