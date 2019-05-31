#pragma once

#include <mutex>

template <unsigned int N>
class Barrier {

public:

  void enter() {
    {
      std::unique_lock<std::mutex> lock{m_own};
      ++m_arrive;
      if (m_arrive == N) {
        m_flag = false;
      }
    }
    while (m_flag);
  }

private:

  unsigned int m_arrive = 0;
  unsigned int m_leave = N;
  bool m_flag = true;
  std::mutex m_own;

};
