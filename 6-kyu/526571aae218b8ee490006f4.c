#include <stddef.h>

size_t countBits(unsigned value)
{
    int number_of_ones = 0;
    for (int i = 0; i < sizeof(value) * 8; i++)
    {
        if ((value >> i) & 1)
            number_of_ones++;
    }
    return number_of_ones;
}
