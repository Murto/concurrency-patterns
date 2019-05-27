#pragma once

#include <list>
#include <mutex>
#include <thread>

class ActiveObject {

public:
  
  ActiveObject();

  ~ActiveObject();

  void add_one();

  void add_two();

  int count() const;

private:

  int m_count = 0;
  std::list<void(ActiveObject::*)()> m_dispatch_queue;
  std::mutex m_own_dispatch_queue;
  std::thread m_dispatch_worker;
  bool m_exit_signal = false;

  void actually_add_one();

  void actually_add_two();

};
