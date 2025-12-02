#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"

struct io_file_data *io_read_file(const char *path)
{
    FILE *fp = fopen(path, "r");
    if (!fp)
        return NULL;

    struct io_file_data *data = NULL;
    char **lines = NULL;
    uint16_t cap = 0;
    uint16_t cnt = 0;
    char buf[256];

    while (fgets(buf, sizeof(buf), fp)) {
        if (cnt >= cap) {
            cap = cap ? (uint16_t)(cap << 1) : 1;
            lines = realloc(lines, cap * sizeof(char *));
            if (!lines)
                goto err;
        }

        buf[strcspn(buf, "\n")] = '\0';

        uint16_t len = (uint16_t)strlen(buf) + 1;
        lines[cnt] = malloc(len);
        if (!lines[cnt])
            goto err;
        memcpy(lines[cnt], buf, len);
        cnt++;
    }

    data = malloc(sizeof(*data));
    if (!data)
        goto err;

    fclose(fp);
    data->lines = lines;
    data->len = cnt;
    return data;

err:
    fclose(fp);
    io_free_file_data(data);
    return NULL;
}

void io_free_file_data(struct io_file_data *data)
{
    if (!data)
        return;
    for (uint16_t i = 0; i < data->len; i++)
        free(data->lines[i]);
    free(data->lines);
    free(data);
}