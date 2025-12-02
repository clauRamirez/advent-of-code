#ifndef IO_H
#define IO_H

#include <stdint.h>

struct file_data {
    char **lines;
    uint16_t len;
};

struct file_data *read_file(const char *path);
void free_file_data(struct file_data *data);

#endif