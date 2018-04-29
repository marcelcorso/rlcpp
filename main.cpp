#include <chrono>
#include <iostream>
#include <thread>

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

class Limiter {

  int rps;
  void (*limited)();

public:
  // rps is requests per second and limited is the function to be rate limited
  Limiter(int rps, void (*limited)()) {
    this->limited = limited;
    this->rps = rps;
  }

  void call() {
    std::this_thread::sleep_for(1s / rps);
    limited();
  }
};

int main(void) {
  using namespace std::literals::chrono_literals;

  Limiter limiter(1, printer_limited);
  limiter.call();
  limiter.call();
  limiter.call();

  return (0);
}
