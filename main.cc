#include <chrono>
#include <iostream>
#include <thread>

#include "dumb.h"
#include "timer.h"

using namespace std;

bool first_call = true;
std::chrono::time_point<std::chrono::high_resolution_clock> last_call;

void printer_callback(std::string message) {
  auto now = std::chrono::high_resolution_clock::now();
  if (!first_call) {
    auto diff =
        now.time_since_epoch().count() - last_call.time_since_epoch().count();

    std::cout << message << ": " << diff / 1E9 << "\n";
  } else {
    first_call = false;
    std::cout << message << ": 0 \n";
  }
  last_call = now;
}

int main(void) {
  DumbLimiter limiter(1, printer_callback);
  limiter.call("dumb 1");
  limiter.call("dumb 2");
  limiter.call("dumb 3");

  TimerLimiter tl(1, printer_callback);
  tl.call("timer alpha");
  tl.call("timer beta");
  tl.call("timer gamma");
  tl.join();

  return (0);
}
