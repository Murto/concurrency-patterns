#include "ReaderWriter.hpp"

#include <thread>

int main() {

  ReaderWriter<std::vector> safe_vector;

  std::thread reporter{[safe_vector&] {
    bool size;
    do {
      safe_vector.read([size&] (const auto& vector) {
        size = vector.size();
      });
    } while (size < 1000);
  }};

  std::thread filler{[safe_vector&] {
    for (int i = 0; i < 1000; ++i) {
      safe_vector.write([i] (auto& vector) {
        vector.push_back(i);
      });
    }
  }

  reporter.join();
  filler.join();

}
