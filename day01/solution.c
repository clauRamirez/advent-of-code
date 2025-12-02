#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "../lib/io.h"

static int16_t calc_distance(const char *move)
{
    int16_t dist = atoi(move + 1);
    return move[0] == 'L' ? dist * -1 : dist;
}

static uint16_t solution_1(const char *path)
{
    struct file_data *data = read_file(path);
    if (!data)
        return 0;

    uint16_t cnt = 0;
    int16_t pos = 50;

    for (uint16_t i = 0; i < data->len; i++) {
        pos += calc_distance(data->lines[i]);
        pos %= 100;
        if (pos < 0)
            pos += 100;

        if (pos == 0)
            cnt++;
    }

    free_file_data(data);

    return cnt;
}

int main(void)
{
    printf("solution 1: %u\n", solution_1("day01/input.txt"));
    return 0;
}