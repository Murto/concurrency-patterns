#include "Balker.hpp"

#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

void Balker::do_long_job() {
  {
    std::lock_guard<std::mutex> lock(m_own_long_job);
    if (m_long_job_in_progress) {
      return;
    } 
    m_long_job_in_progress = true;
  }

  std::cout << "Progress [" << std::flush;

  for (auto i = 0; i < 10; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    std::cout << '#' << std::flush;
  }
  std::cout << "]\n\nDone!\n";

  m_long_job_in_progress = false;
}


