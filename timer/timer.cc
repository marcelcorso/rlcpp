#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

#include "timer.h"

using namespace std;

void TimerLimiter::worker() {
  while (1) {
    std::string message;
    {
      std::lock_guard<std::mutex> lk(this->mutex);
      message = this->queue.front();
      if (message.size() > 0) {
        this->queue.pop();
      }
    }
    if (message.size() > 0) {
      this->callback(message);
    }
    std::this_thread::sleep_for(1s / rps);
  }
}

TimerLimiter::TimerLimiter(int rps, void (*callback)(std::string message)) {
  this->callback = callback;
  this->rps = rps;

  this->thread = std::thread(&TimerLimiter::worker, this);
}

void TimerLimiter::call(std::string message) {
  std::lock_guard<std::mutex> guard(this->mutex);
  this->queue.push(message);
}

void TimerLimiter::join() { this->thread.join(); }
