#include <stdio.h>
#include <time.h>

#define BUFFSIZE 1024

typedef char *option[2];

unsigned int optionprompt(unsigned int count, option *options);

void readline(char buffer[BUFFSIZE]);
void fileprompt(char buffer[BUFFSIZE]);
void fileopen(char filename[BUFFSIZE], FILE **fp);
long int timems();