#include <stdint.h>
#include <stdlib.h>
#include "math.h"

uint64_t *math_range(uint64_t start, uint64_t end, uint64_t *count)
{
    uint64_t *out = malloc((end - start + 1) * sizeof(uint64_t));
    if (!out) {
        *count = 0;
        return NULL;
    }

    uint64_t cnt = 0;
    for (uint64_t i = start; i < end; i++) {
        out[cnt] = i;
        cnt++;
    }

    *count = cnt;
    return out;
}