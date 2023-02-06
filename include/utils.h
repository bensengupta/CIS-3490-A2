#include <stdio.h>

#ifndef UTILS_H
#define UTILS_H

#define BUFFSIZE 1024

void readline(char buffer[BUFFSIZE]);
void fileprompt(char buffer[BUFFSIZE]);
void fileopen(char filename[BUFFSIZE], FILE **fp);
long int millis();
int promptint(int min, int max);

#endif /* UTILS_H */