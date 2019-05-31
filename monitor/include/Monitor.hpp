#pragma once

#include <mutex>

template <typename Type>
class Monitor {

public:

  class MonitorHelper {

  public:

    MonitorHelper(Monitor* monitor)
    :  m_monitor{monitor}, m_lock{monitor->m_own} {}

    Type* operator->() {
      return &m_monitor->m_value;
    }

  private:

    Monitor* m_monitor;
    std::unique_lock<std::mutex> m_lock;

  };

  template <typename ...Args>
  Monitor(Args&&... args)
  : m_value{args...} {}

  MonitorHelper operator->() {
    return MonitorHelper{this};
  }

  const Type& value() {
    return m_value;
  }

private:

  Type m_value;
  std::mutex m_own;

};
