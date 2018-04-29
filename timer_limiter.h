#include <chrono>
#include <iostream>
#include <queue>
#include <thread>

using namespace std;

class TimerLimiter {
  int rps;
  void (*limited)();

  std::thread *m_thread;
  std::queue<ThreadMsg *> m_queue;

  void worker();

public:
  // "rps" is requests per second and "limited" is the function to be rate
  // limited
  TimerLimiter(int rps, void (*limited)());
  void call();
}
