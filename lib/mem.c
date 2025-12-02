#include <stdlib.h>
#include <stdint.h>
#include "mem.h"

void mem_free_str_array(char **arr, uint64_t count)
{
    if (!arr)
        return;
    for (uint64_t i = 0; i < count; i++)
        free(arr[i]);
    free(arr);
}