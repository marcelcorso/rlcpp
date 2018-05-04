#include <chrono>
#include <iostream>
#include <thread>

#include "dumb.h"

using namespace std;

bool first_call = true;
std::chrono::time_point<std::chrono::high_resolution_clock> last_call;

void printer_limited() {
  auto now = std::chrono::high_resolution_clock::now();
  if (!first_call) {
    auto diff =
        now.time_since_epoch().count() - last_call.time_since_epoch().count();

    std::cout << diff / 1E9 << "\n";
  } else {
    first_call = false;
  }
  last_call = now;
}

int main(void) {
  DumbLimiter limiter(1, printer_limited);
  limiter.call();
  limiter.call();
  limiter.call();

  return (0);
}
