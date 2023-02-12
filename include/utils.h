/**
 * CIS3490 - Assignment 2
 * Author: Benjamin Sengupta
 * ID: 1188767
 * Date: 2023-Feb-11
 */

#include <stdio.h>

#ifndef UTILS_H
#define UTILS_H

// Size of most char buffers
#define BUFFSIZE 1024

// Reads a line from stdin and stores it in buffer, discards the line break
void readline(char buffer[BUFFSIZE]);
// Prompts for a filename and stores input in buffer
void fileprompt(char buffer[BUFFSIZE]);
// Opens a file for reading, exits if file does not exist
void fileopen(char filename[BUFFSIZE], FILE **fp);
// Returns the time in milliseconds since the start of the program
long int millis();

#endif /* UTILS_H */