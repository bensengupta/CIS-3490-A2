---
course: CIS3490
title: Assignment 2 – Algorithm Design
author: Benjamin Sengupta
student-id: 1188767
date: 2023-02-11
---

# CIS3490 Assignment 2

*Benjamin Sengupta 1188787*

## Compile & Run

```bash
# Build executables
make release

# 1.1 Counting Inversions Brute Force
# NOTE: filename will be prompted
./bin/P11

# 1.2 Counting Inversions Divide and Conquer
# NOTE: filename will be prompted
./bin/P12

# 2.1 Convex Hull Brute Force & Shortest Path
# NOTE: data_A2_Q2.txt required in working directory
#       may take ~20 seconds to produce output
./bin/P21

# 2.2 Convex Hull Divide and Conquer & Shortest Path
# NOTE: data_A2_Q2.txt required in working directory
./bin/P22
```

## Sample output

```
$ make release

rm -f objects/*.o bin/*
gcc -std=c99 -Wall -Wextra -O2 -c src/P1utils.c -o objects/P1utils.o
gcc -std=c99 -Wall -Wextra -O2 -c src/utils.c -o objects/utils.o
gcc -std=c99 -Wall -Wextra -O2 src/P11.c objects/P1utils.o objects/utils.o -o bin/P11
gcc -std=c99 -Wall -Wextra -O2 src/P12.c objects/P1utils.o objects/utils.o -o bin/P12
gcc -std=c99 -Wall -Wextra -O2 -c src/P2utils.c -o objects/P2utils.o
gcc -std=c99 -Wall -Wextra -O2 src/P21.c objects/P2utils.o objects/utils.o -o bin/P21 -lm
gcc -std=c99 -Wall -Wextra -O2 src/P22.c objects/P2utils.o objects/utils.o -o bin/P22 -lm
```

```
$ ./bin/P11

filename:
> data_A2_Q1.txt
50000 numbers loaded from 'data_A2_Q1.txt'

time=264ms
inversions=623897407
```

```
$ ./bin/P12

filename:
> data_A2_Q1.txt
50000 numbers loaded from 'data_A2_Q1.txt'

time=11ms
inversions=623897407
```

```
$ ./bin/P21

30000 points loaded from 'data_A2_Q2.txt'
computing convex hull

time: 14656ms
convex hull (22 points):
idx        x       y
  0   1156.3    24.3
  1   3943.7    32.0
  2   5616.9    37.6
  3   6265.4    73.0
  4   6434.5  1065.1
  5   6416.4  3607.9
  6   6382.1  5517.2
  7   6163.4  6092.8
  8   5961.6  6274.5
  9   5561.2  6328.5
 10   4336.6  6384.0
 11   3839.0  6397.2
 12   2238.7  6426.4
 13   1769.3  6414.2
 14    484.1  6266.3
 15    128.3  6091.3
 16    120.9  6008.0
 17     30.8  3064.0
 18     28.3  1205.6
 19    122.9   621.9
 20    145.7   517.0
 21    272.6   240.1

==== compute shortest path ====
enter coordinates of starting point:
e.g. 1156.3 24.3
> 120.9  6008.0
enter coordinates of ending point:
> 272.6   240.1

shortest path (length: 5807.0) (6 points):
idx        x       y
  0    120.9  6008.0
  1     30.8  3064.0
  2     28.3  1205.6
  3    122.9   621.9
  4    145.7   517.0
  5    272.6   240.1
```

```
$ ./bin/P22

30000 points loaded from 'data_A2_Q2.txt'
computing convex hull

time: 0ms
convex hull (22 points):
idx        x       y
  0   1156.3    24.3
  1   3943.7    32.0
  2   5616.9    37.6
  3   6265.4    73.0
  4   6434.5  1065.1
  5   6416.4  3607.9
  6   6382.1  5517.2
  7   6163.4  6092.8
  8   5961.6  6274.5
  9   5561.2  6328.5
 10   4336.6  6384.0
 11   3839.0  6397.2
 12   2238.7  6426.4
 13   1769.3  6414.2
 14    484.1  6266.3
 15    128.3  6091.3
 16    120.9  6008.0
 17     30.8  3064.0
 18     28.3  1205.6
 19    122.9   621.9
 20    145.7   517.0
 21    272.6   240.1

==== compute shortest path ====
enter coordinates of starting point:
e.g. 1156.3 24.3
> 120.9  6008.0
enter coordinates of ending point:
> 272.6   240.1

shortest path (length: 5807.0) (6 points):
idx        x       y
  0    120.9  6008.0
  1     30.8  3064.0
  2     28.3  1205.6
  3    122.9   621.9
  4    145.7   517.0
  5    272.6   240.1
```