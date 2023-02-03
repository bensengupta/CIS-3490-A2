#include "../include/P2utils.h"
#include "../include/utils.h"

// Solution 1: Brute Force
// Time Complexity: O(n^2)
algresult convexhullbruteforce(vector vec) {
  vector path;
  vectorinit(&path);
  algresult res = {0.0, path};

  // Algorithm here

  return res;
}

int main(void) {
  eval(convexhullbruteforce);
  return 0;
}