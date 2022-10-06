#include "radix.h"

const char RADIX_TABLE[17] = "0123456789ABCDEF";

int calc_rlen(int value, const int radix) {
    int rlen = 1 + (value < 0 ? 1 : 0);
    if (value > -2 && value < 2)
        rlen += 1;
    else {
        float f = log2f(value < 0 ? -value : value) / log2f(radix);
        rlen += f + 1;
    }
    return rlen;
}

int radix_conv(int value, const int radix, char* buffer, const int len) {
    if (radix < 2 || radix > 16)
        return INVALID_RADIX_SPECIFIED;                         // judge radix selection
    int rlen = calc_rlen(value, radix);                         // calculate result string length
    if (len < rlen)
        return BUFFER_LENGTH_OVERFLOW;                          // give error feedback
    if (value < 0)
        buffer[0] = '-', value = -value;                        // negative handle
    for (int i = rlen - 2; i >= 0 && value; value /= radix, i--)
        buffer[i] = RADIX_TABLE[value % radix];                 // generate results
    buffer[rlen - 1] = 0;                                           // make buffer C-style string
    return rlen;
}