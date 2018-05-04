#pragma once

#include <string>

class DumbLimiter {

  int rps;
  void (*callback)(std::string message);

public:
  // "rps" is requests per second and "limited" is the function to be rate
  // limited
  DumbLimiter(int rps, void (*callback)(std::string message));

  void call(std::string message);
};
