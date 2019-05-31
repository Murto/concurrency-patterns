#include "Monitor.hpp"

#include <iostream>
#include <set>
#include <thread>
#include <vector>


int main() {
  constexpr int NUMBER_COUNT = 10000;
  constexpr int THREAD_COUNT = 4;
  std::vector<std::thread> threads;
  Monitor<std::set<int>> monitor;
  for (int i = 0; i <  THREAD_COUNT; ++i) {
    threads.emplace_back([NUMBER_COUNT, THREAD_COUNT, &monitor, i] {
      int begin = i * (NUMBER_COUNT / THREAD_COUNT);
      int end = begin + (NUMBER_COUNT / THREAD_COUNT);
      for (int i = begin; i < end; ++i) {
        monitor->insert(i);
      }
    });
  }
  for (auto& thread : threads) {
    thread.join();
  }
  for (int i = 0; i < NUMBER_COUNT; ++i) {
    if (monitor.value().find(i) == monitor.value().end()) {
      std::cout << "Number " << i << " lost! Something is wrong with this monitor...\n";
      return 1;
    }
  }
  std::cout << "All numbers present!\n";
  return 0;
}
