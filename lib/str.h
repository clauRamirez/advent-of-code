#ifndef STR_H
#define STR_H

#include <stdint.h>

char *str_cp(const char *str);
char **str_split(const char *in, char *delim, uint64_t *count);

#endif