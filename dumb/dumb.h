

class DumbLimiter {

  int rps;
  void (*limited)();

public:
  // "rps" is requests per second and "limited" is the function to be rate
  // limited
  DumbLimiter(int rps, void (*limited)());

  void call();
};
