#include <stdio.h>
#include <time.h>

#define BUFFSIZE 1024

typedef struct vector {
  unsigned int size;
  unsigned int capacity;
  unsigned long int *nums;
} vector;

typedef char *option[2];

unsigned int optionprompt(unsigned int count, option *options);

void readline(char buffer[BUFFSIZE]);
void fileprompt(char buffer[BUFFSIZE]);
void fileopen(char filename[BUFFSIZE], FILE **fp);
void fileread(FILE *file, vector *vec);

void vectorinit(vector *vec);
void vectorcopy(vector *dest, vector *src);
void vectoradd(vector *vec, unsigned long int x);
void vectorfree(vector *vec);
void vectorprint(vector vec);
long int timems();