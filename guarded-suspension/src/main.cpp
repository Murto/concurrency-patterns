#include "SuspendedQueue.hpp"

#include <chrono>
#include <iostream>
#include <thread>

int main() {
  SuspendedQueue<int> queue;
  std::thread reader{[&queue] {
    std::cout << "First: " << queue.front() << '\n';
    queue.pop();
    std::cout << "Second: " << queue.front() << '\n';
    queue.pop();
    std::cout << "Third: " << queue.front() << '\n';
    queue.pop();
  }};
  std::thread writer{[&queue] {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    queue.push(1);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    queue.push(2);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    queue.push(3);
  }};
  reader.join();
  writer.join();
}
