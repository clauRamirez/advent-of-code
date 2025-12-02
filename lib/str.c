#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "str.h"
#include "mem.h"

char *str_cp(const char *str)
{
    uint64_t len = (uint64_t)strlen(str) + 1;
    char *copy = malloc(len);
    if (!copy)
        return NULL;
    memcpy(copy, str, len);
    return copy;
}

char **str_split(const char *in, char *delim, uint64_t *count)
{
    char *cp = str_cp(in);
    if (!cp)
        return NULL;

    char **out = NULL;
    uint64_t cap = 0;
    uint64_t cnt = 0;

    char *token = strtok(cp, delim);
    while (token) {
        if (cnt >= cap) {
            cap = cap ? (uint64_t)(cap << 1) : 8;
            char **tmp = realloc(out, cap * sizeof(char *));
            if (!tmp)
                goto err_alloc;
            out = tmp;
        }

        uint64_t tlen = (uint64_t)strlen(token) + 1;
        out[cnt] = malloc(tlen);
        if (!out[cnt])
            goto err_alloc;

        memcpy(out[cnt], token, tlen);
        cnt++;
        token = strtok(NULL, delim);
    }

    free(cp);
    *count = cnt;
    return out;

err_alloc:
    mem_free_str_array(out, cnt);
    free(cp);
    return NULL;
}