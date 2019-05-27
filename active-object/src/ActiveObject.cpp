#include "ActiveObject.hpp"

#include <mutex>
#include <thread>

ActiveObject::ActiveObject() {
  m_dispatch_worker = std::thread([this] {
    do {
      std::lock_guard<std::mutex> lock{m_own_dispatch_queue};
      while (!this->m_dispatch_queue.empty()) {
        auto f = this->m_dispatch_queue.front();
        (this->*f)();
        this->m_dispatch_queue.pop_front();
      }
    } while (!this->m_exit_signal);
  });
}

ActiveObject::~ActiveObject() {
  m_exit_signal = true;
  m_dispatch_worker.join();
}

void ActiveObject::add_one() {
  std::lock_guard<std::mutex> lock{m_own_dispatch_queue};
  m_dispatch_queue.push_back(&ActiveObject::actually_add_one);
}

void ActiveObject::add_two() {
  std::lock_guard<std::mutex> lock{m_own_dispatch_queue};
  m_dispatch_queue.push_back(&ActiveObject::actually_add_two);
}

int ActiveObject::count() const {
  return m_count;
}

void ActiveObject::actually_add_one() {
  m_count += 1;
}

void ActiveObject::actually_add_two() {
  m_count += 2;
}
