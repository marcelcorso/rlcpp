#include <chrono>
#include <iostream>
#include <thread>

#include "dumb.h"

using namespace std;
using namespace std::literals::chrono_literals;

// "rps" is requests per second and "limited" is the function to be rate
// limited
DumbLimiter::DumbLimiter(int rps, void (*limited)()) {
  this->limited = limited;
  this->rps = rps;
}

void DumbLimiter::call() {
  std::this_thread::sleep_for(1s / rps);
  limited();
}
