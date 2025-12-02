#ifndef IO_H
#define IO_H

#include <stdint.h>

struct io_file_data {
    char **lines;
    uint16_t len;
};

struct io_file_data *io_read_file(const char *path);
void io_free_file_data(struct io_file_data *data);

#endif