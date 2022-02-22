// Include libraries to open files
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

char* read_file(char* filename)
{
    // Open file
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    // Get file size
    struct stat st;
    if (fstat(fd, &st) == -1) {
        perror("fstat");
        exit(1);
    }
    int size = st.st_size;

    // Read file
    char* buffer = malloc(size + 1);
    if (read(fd, buffer, size) == -1) {
        perror("read");
        exit(1);
    }
    buffer[size] = '\0';

    // Close file
    if (close(fd) == -1) {
        perror("close");
        exit(1);
    }

    return buffer;
}

void write_file(char* filename, char* buffer)
{
    // Open file
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    // Write file
    if (write(fd, buffer, strlen(buffer)) == -1) {
        perror("write");
        exit(1);
    }

    // Close file
    if (close(fd) == -1) {
        perror("close");
        exit(1);
    }
}