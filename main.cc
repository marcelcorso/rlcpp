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

void call_many(TimerLimiter *tl, std::string name) {
  std::cout << "pingo" << name;
  // tl->call(name + ": timer alpha");
  // tl->call(name + ": timer beta");
  // tl->call(name + ": timer gamma");
}

int main(void) {
  DumbLimiter limiter(1, printer_callback);
  limiter.call("dumb 1");

  TimerLimiter tl(1, printer_callback);
  std::thread tt1(call_many, &tl, "one");
  std::thread tt2(call_many, &tl, "two");
  std::thread tt3(call_many, &tl, "three");

  tl.join();
  tt1.join();
  tt2.join();
  tt3.join();

  return (0);
}
