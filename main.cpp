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

  void (*limited)();

public:
  Limiter(void (*limited)()) { this->limited = limited; }

  void call() {
    std::this_thread::sleep_for(2s);
    limited();
  }
};

int main(void) {
  using namespace std::literals::chrono_literals;

  Limiter limiter(printer_limited);
  limiter.call();
  limiter.call();

  /*
  printer_limited();
  std::cout << std ::flush;
  std::this_thread::sleep_for(2s);
  printer_limited();
  */
  return (0);
}
