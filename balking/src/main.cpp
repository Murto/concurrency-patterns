#include "Balker.hpp"

#include <iostream>
#include <thread>
#include <utility>

void try_do_long_job(Balker& balker) {
  balker.do_long_job();
}

int main() {
  Balker balker;
  std::thread attempt_1(try_do_long_job, std::ref(balker));
  std::thread attempt_2(try_do_long_job, std::ref(balker));
  std::thread attempt_3(try_do_long_job, std::ref(balker));
  attempt_1.join();
  attempt_2.join();
  attempt_3.join();
  return 0;
}
