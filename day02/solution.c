#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/io.h"
#include "../lib/math.h"
#include "../lib/str.h"
#include "../lib/mem.h"

#define UINT64_SIZE 20
#define UINT64_HALF_SIZE (UINT64_SIZE / 2)
#define INPUT_FILE "day02/input.txt"

void aggregate_invalid_passwds(uint64_t *rng, uint64_t rlen, uint64_t *agg)
{
    for (uint64_t i = 0; i < rlen; i++) {
        char str[UINT64_SIZE + 1]; // +1 for null terminator
        snprintf(str, sizeof(str), "%lu", rng[i]);

        uint64_t len = (uint64_t)strlen(str);

        if (len % 2 != 0)
            continue;

        uint64_t mid = len / 2;

        char left[UINT64_HALF_SIZE + 1] = {0}; // +1 for null terminator
        char right[UINT64_HALF_SIZE + 1] = {0};

        strncpy(left, str, mid);
        left[mid] = '\0';
        strcpy(right, str + mid);

        if (strcmp(left, right) == 0)
            *agg += rng[i];
    }
}

uint64_t solution_1(struct io_file_data *data)
{
    uint64_t total = 0;
    for (uint64_t i = 0; i < data->len; i++) {
        uint64_t ilen = 0;
        char **values = str_split(data->lines[i], ",", &ilen);
        if (!values)
            continue;

        for (uint64_t j = 0; j < ilen; j++) {
            uint64_t jlen = 0;
            char **pair = str_split(values[j], "-", &jlen);
            if (!pair || jlen != 2)
                continue;

            uint64_t x = strtoul(pair[0], NULL, 10);
            uint64_t y = strtoul(pair[1], NULL, 10);

            uint64_t rlen = 0;
            uint64_t *rng = math_range(x, y + 1, &rlen);
            if (!rng)
                mem_free_str_array(pair, jlen);

            aggregate_invalid_passwds(rng, rlen, &total);
            free(rng);
        }

        mem_free_str_array(values, ilen);
    }

    return total;
}

int main(void)
{
    struct io_file_data *data = io_read_file(INPUT_FILE);
    if (!data)
        return 1;

    uint64_t result = solution_1(data);
    io_free_file_data(data);

    printf("%lu\n", result);
    return 0;
}
