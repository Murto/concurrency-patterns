#pragma once

#include <mutex>
#include <shared_mutex>

template <typename Type>
class ReaderWriter {

public:

  template <typename ...Args>
  ReaderWriter(Args&&... args)
  : m_resource{args} {}

  template <typename CallbackType>
  void read(CallbackType callback) const {
    std::shared_lock lock{m_own};
    callback(m_resource);
  }

  template <typename CallbackType>
  void write(CallbackType callback) {
    std::unique_lock lock{m_own};
    callback(m_resource);
  }

private:

  Type m_resource;
  std::shared_mutex m_own;

};
