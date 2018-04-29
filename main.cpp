#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

bool first_call = true;
std::chrono::time_point<std::chrono::high_resolution_clock> last_call;

void ratelimited() {
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
  using namespace std::literals::chrono_literals;
  ratelimited();
  std::cout << std ::flush;
  std::this_thread::sleep_for(2s);
  ratelimited();
  return (0);
}
