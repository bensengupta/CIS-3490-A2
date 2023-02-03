#include "../include/P1utils.h"
#include "../include/utils.h"

// Merge sort will sort vec in-place
// Note: stop is non-inclusive
long int mergesort(vector vec, int start, int stop) {
  // Base case: length 0 or 1
  if (start >= stop - 1) {
    return 0;
  }

  long int inversions = 0;

  // Divide recursively
  int mid = start + (stop - start) / 2;

  int lstart = start;
  int lstop = mid;
  int rstart = mid;
  int rstop = stop;

  inversions += mergesort(vec, lstart, lstop);
  inversions += mergesort(vec, rstart, rstop);

  // Merge
  vector sorted;
  vectorinit(&sorted);

  int i = lstart;
  int j = rstart;
  while (i < lstop && j < rstop) {
    if (vec.items[i] <= vec.items[j]) {
      vectoradd(&sorted, vec.items[i]);
      i++;
    } else {
      vectoradd(&sorted, vec.items[j]);
      inversions += (lstop - i);
      j++;
    }
  }

  while (i < lstop) {
    vectoradd(&sorted, vec.items[i]);
    i++;
  }
  while (j < rstop) {
    vectoradd(&sorted, vec.items[j]);
    j++;
  }

  // Copy over to original array
  for (int i = 0; i < sorted.size; i++) {
    vec.items[start + i] = sorted.items[i];
  }

  vectorfree(&sorted);

  return inversions;
}

// Solution 2: Divide And Conquer
// Time Complexity: O(n log n)
long int divideandconquerinversions(vector vec) {
  vector copy;
  vectorinit(&copy);
  vectorcopy(&copy, &vec);
  return mergesort(copy, 0, copy.size);
}

int main(void) {
  eval(divideandconquerinversions);
  return 0;
}