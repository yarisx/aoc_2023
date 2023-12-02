#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

int main(int argc, char** argv)
{
    if (argc < 2) return -1;

    FILE *in = fopen(argv[1], "r");
    uint64_t game_ctr = 0;

    while (! feof(in))
    {
        uint64_t counters[3] = {0};
        size_t bufsize = 0;
        char *buf = NULL;
        char *ptr = NULL, *ptr2 = NULL;

        if (-1 == getline(&buf, &bufsize, in))
        {
            break;
        }
        ptr = buf;
        for (;*ptr != '\n';)
        {
            long tmp_val = 0;
            size_t ctr_idx = 0;
            tmp_val = strtol(ptr, &ptr2, 10);

            switch (*ptr2)
            {
                case 'r':
                    ctr_idx = 0;
                break;
                case 'g':
                    ctr_idx = 1;
                break;
                case 'b':
                    ctr_idx = 2;
                break;
            }
            if (tmp_val > counters[ctr_idx])
            {
                counters[ctr_idx] = tmp_val;
            }
            ptr = ptr2 + 1;
        }
        game_ctr += counters[0] * counters[1] * counters[2];
        memset(counters, 0, sizeof(counters));
        memset(buf, 0, bufsize);
    }
    printf("Combined power is: %"PRIu64"\n", game_ctr);
    return 0;
}
