#include "tools.h"

#include <random>

// Random device
std::mt19937 rng(time(nullptr));

// Random number generator. Use int random(lowest,highest);
int random(int low, int high) {
  std::uniform_int_distribution<int> dist(
      low, high);  // distribution in range [1, 6]
  return dist(rng);
}
