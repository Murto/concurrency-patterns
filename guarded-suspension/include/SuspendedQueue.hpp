#pragma once

#include <queue>
#include <mutex>

template <typename QueueType>
class SuspendedQueue {

public:

  void push(const QueueType& element) {
    std::lock_guard<std::mutex> lock{m_own};
    m_queue.push(element);
  }

  void pop() {
    while (true) {
      std::unique_lock<std::mutex> lock{m_own};
      if (m_queue.size() == 0) {
        continue;
      } else {
        m_queue.pop();
        return;
      }
    }
  }

  QueueType& front() {
    while (true) {
      std::unique_lock<std::mutex> lock{m_own};
      if (m_queue.size() == 0) {
        continue;
      } else {
        return m_queue.front();
      }
    }
  }

private:

  std::queue<QueueType> m_queue;
  std::mutex m_own;

};
