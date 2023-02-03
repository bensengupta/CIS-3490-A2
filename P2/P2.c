#include <string.h>

#include "../utils/utils.h"
#include "P2utils.h"

typedef struct result {
  float length;
  vector path;
} result;

result solutionbruteforce(vector vec);
result solutiondivideandconquer(vector vec);

int main(void) {
  FILE *file;
  char buffer[BUFFSIZE];
  vector points;
  long int start, end;
  result res;

  vectorinit(&points);

  fileprompt(buffer);
  fileopen(buffer, &file);
  fileread(file, &points);
  fclose(file);

  printf("file found!\n");

  printf("debug: vector size %d\n", points.size);

  option options[] = {
      {"b", "brute force"},
      {"d", "divide and conquer"},
  };

  start = timems();
  switch (optionprompt(2, options)) {
    case 0:
      printf("brute force started\n");
      res = solutionbruteforce(points);
      break;
    case 1:
      printf("divide and conquer started\n");
      res = solutiondivideandconquer(points);
      break;
  }
  end = timems();

  printf("Elapsed=%ldms NumPoints=%d Length=%f\n", end - start, res.path.size,
         res.length);
  for (int i = 0; i < res.path.size; i++) {
    point p = res.path.items[i];
    printf("  Point %04.1f %04.1f\n", p.x, p.y);
  }

  vectorfree(&points);

  return 0;
}

// Solution 1: Brute Force
// Time Complexity: O(n^2)
result solutionbruteforce(vector vec) {
  vector path;
  vectorinit(&path);
  result res = {0.0, path};

  // Algorithm here

  return res;
}

// Solution 2: Divide And Conquer
// Time Complexity: O(n log n)
result solutiondivideandconquer(vector vec) {
  vector path;
  vectorinit(&path);
  result res = {0.0, path};

  // Algorithm here

  return res;
}
