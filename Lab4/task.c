#include <stdio.h>

int main(int argc, char const *argv[]) {
    if (argc < 2)
        return 1;
    unsigned int x;
    sscanf(argv[1], "%u", &x);
    int trueCount = 0;
    for (unsigned int mask = 1; mask > 0; mask <<= 1)
        trueCount += (x & mask) ? 1 : 0;
    printf("Your number was %u\n"
        "In %u, there are %u bits set to 1.\n", x, x, trueCount);
}