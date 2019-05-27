#include "ActiveObject.hpp"

#include <chrono>
#include <iostream>
#include <thread>
#include <utility>

void add_one_to_counter(ActiveObject& counter) {
  const auto ADD_COUNT = 1000;
  for (auto i = 0; i < ADD_COUNT; ++i) {
    counter.add_one();
  }
}

void add_two_to_counter(ActiveObject& counter) {
  const auto ADD_COUNT = 1000;
  for (auto i = 0; i < ADD_COUNT; ++i) {
    counter.add_two();
  }
}

int main() {
  ActiveObject counter;
  std::thread one_adder(add_one_to_counter, std::ref(counter));
  std::thread two_adder(add_two_to_counter, std::ref(counter));
  one_adder.join();
  two_adder.join();
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  std::cout << "Final count:    " << counter.count() << '\n';
  std::cout << "Expected count: " << 3000 << '\n';
  return 0;
}
