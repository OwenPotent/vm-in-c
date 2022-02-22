#pragma once
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// A function to read a file into a string
char *read_file(char *filename);


// A function to write a string to a file
void write_file(char *filename, char* buffer);