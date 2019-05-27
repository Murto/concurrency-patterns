#pragma once

#include <mutex>

class Balker {

public:

  void do_long_job();

private:

  bool m_long_job_in_progress = false;
  std::mutex m_own_long_job;

};
