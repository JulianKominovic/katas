## 6 kyu

### Bit counting

#### Links

- https://www.codewars.com/kata/526571aae218b8ee490006f4
- [My solution](./6-kyu/526571aae218b8ee490006f4.c)
- [Bitwise operators](https://www.geeksforgeeks.org/bitwise-operators-in-c-cpp/)
- [Bitwise calculator](https://bitwisecmd.com/)

#### Explanation

This kata is about counting bits 1 on an integer.

GCC has a `__builtin__popcount(int)` which I could use but I didn't know about it.

1. I used a for loop to iterate over the bits of the integer (32 bits).
2. In each iteration I bit shifted the integer to the right by `i` bits and then I used the `&` operator with `1` to check if the lower bit of the integer is 1.
3. If it is, I increment the counter.

Another alternative: https://stackoverflow.com/a/51388846

```c
#include <stddef.h>

size_t countBits(unsigned n)
{
    n = (n & 0x55555555u) + ((n >> 1) & 0x55555555u);
    n = (n & 0x33333333u) + ((n >> 2) & 0x33333333u);
    n = (n & 0x0f0f0f0fu) + ((n >> 4) & 0x0f0f0f0fu);
    n = (n & 0x00ff00ffu) + ((n >> 8) & 0x00ff00ffu);
    n = (n & 0x0000ffffu) + ((n >>16) & 0x0000ffffu);
    return n;
}
```

### Lottery ticket

#### Links

- https://www.codewars.com/kata/57f625992f4d53c24200070e
- [My solution](./6-kyu/57f625992f4d53c24200070e.c)
- [ASCII Table](https://www.ascii-code.com/)

#### Explanation

1. Characters can be casted as integers following the ASCII table.
2. Char\* can be iterated as an array, and end with a null terminator (\0 or 0 in decimal).
3. I used a for loop to iterate over the mini_wins of the ticket.
4. Read mini_win letter and cast it to an integer.
5. If the char as an integer is equal to the win number, increment the counter.
6. If the counter is equal to the mini_win size, return "Winner!".
7. If the counter is not equal to the mini_win size, return "Loser!".

#### Notes

Have some problemas with this kata, it seems it has some bugs in the tests.
