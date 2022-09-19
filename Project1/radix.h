#ifndef VICTORHUANG_RADIX
#define VICTORHUANG_RADIX
#include <math.h>

#define INVALID_RADIX_SPECIFIED (-1)
#define BUFFER_LENGTH_OVERFLOW (-2)

int calc_rlen(int value, const int radix);
int radix_conv(int value, const int radix, char* buffer, const int len);

#endif