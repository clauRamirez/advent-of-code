#include "../lib/io.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define INPUT_FILE "day03/input.txt"

uint64_t solution_1(struct io_file_data *data)
{
    uint16_t x = data->len;
    uint16_t y = (uint16_t)strlen(data->lines[0]);
    uint16_t grid[x][y];
    for (uint16_t i = 0; i < x; i++) {
        for (uint16_t j = 0; j < y; j++) {
            grid[i][j] = (uint16_t)(data->lines[i][j] - '0');
        }
    }
    uint64_t result = 0;
    for (uint16_t i = 0; i < x; i++) {
        uint16_t max_joltage = 0;
        for (uint16_t j1 = 0; j1 < y; j1++) {
            for (uint16_t j2 = j1 + 1; j2 < y; j2++) {
                uint16_t joltage = (uint16_t)(grid[i][j1] * 10 + grid[i][j2]);
                if (joltage > max_joltage) {
                    max_joltage = joltage;
                }
            }
        }
        result += max_joltage;
    }

    return result;
}

int main(void)
{
    struct io_file_data *data = io_read_file(INPUT_FILE);
    if (!data)
        return 1;

    uint64_t result = solution_1(data);

    printf("solution 1: %lu\n", result);

    io_free_file_data(data);

    return 0;
}