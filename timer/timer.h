#pragma once

#include <chrono>
#include <iostream>
#include <queue>
#include <string>
#include <thread>

using namespace std;

class TimerLimiter {
  int rps;
  void (*callback)(std::string);

  std::thread thread;
  std::queue<std::string> queue;

  void worker();

public:
  // "rps" is requests per second and "limited" is the function to be rate
  // limited
  TimerLimiter(int rps, void (*callback)(std::string));
  void call(std::string message);
  void join();
};
