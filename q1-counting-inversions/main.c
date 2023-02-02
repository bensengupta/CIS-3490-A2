#include <string.h>

#include "utils.h"

#define DEBUG 1

long int solutionBruteForce(vector vec);
long int solutionDivideAndConquer(vector vec);

int main(void) {
  FILE *file;
  char buffer[BUFFSIZE];
  vector nums;

  vectorinit(&nums);

  if (DEBUG) {
    strcpy(buffer, "data_A2_Q1.txt");
  } else {
    fileprompt(buffer);
  }

  fileopen(buffer, &file);
  fileread(file, &nums);

  // Brute force solution
  long int start = timems();
  long int inversions = solutionDivideAndConquer(nums);
  long int end = timems();

  printf("Elapsed=%ldms Inversions=%ld\n", end - start, inversions);

  vectorfree(&nums);

  return 0;
}

// Solution 1: Brute Force
// Time Complexity: O(n^2)
long int solutionBruteForce(vector vec) {
  long int inversions = 0;

  for (int i = 0; i < vec.size; i++) {
    for (int j = i + 1; j < vec.size; j++) {
      if (vec.nums[i] > vec.nums[j]) {
        inversions++;
      }
    }
  }

  return inversions;
}

// stop is non inclusive
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
    if (vec.nums[i] <= vec.nums[j]) {
      vectoradd(&sorted, vec.nums[i]);
      i++;
    } else {
      vectoradd(&sorted, vec.nums[j]);
      inversions += (lstop - i);
      j++;
    }
  }

  while (i < lstop) {
    vectoradd(&sorted, vec.nums[i]);
    i++;
  }
  while (j < rstop) {
    vectoradd(&sorted, vec.nums[j]);
    j++;
  }

  // Copy over to original array
  for (int i = 0; i < sorted.size; i++) {
    vec.nums[start + i] = sorted.nums[i];
  }

  vectorfree(&sorted);

  return inversions;
}

// Solution 2: Divide And Conquer
// Time Complexity: O(n log n)
long int solutionDivideAndConquer(vector vec) {
  vector copy;
  vectorinit(&copy);
  vectorcopy(&copy, &vec);
  return mergesort(copy, 0, copy.size);
}