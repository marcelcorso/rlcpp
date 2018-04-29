#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

void TimerLimiter::worker() {}

TimerLimiter::TimerLimiter(int rps, void (*limited)()) {
  this->limited = limited;
  this->rps = rps;

  std::thread timerThread(&TimerLimiter::worker, this);
}

void TimerLimiter::call() {
  std::this_thread::sleep_for(1s / rps);
  limited();
}
