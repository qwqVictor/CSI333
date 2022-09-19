#include "radix.h"

const char RADIX_TABLE[17] = "0123456789ABCDEF";
int radix_conv(int value, const int radix, char* buffer, const int len) {
    if (radix < 2 || radix > 16)
        return INVALID_RADIX_SPECIFIED;                         // judge radix selection
    int rlen = value ? (ceil(log2f(value < 0 ? -value : value) / log2f(radix))
                     + (value < 0 ? 1 : 0)) : 1;                // calculate result string length
    if (len <= rlen)
        return BUFFER_LENGTH_OVERFLOW;                          // give error feedback
    if (value < 0)
        buffer[0] = '-', value = -value;                        // negative handle
    for (int i = rlen; i >= 0 && value; value /= radix, i--)
        buffer[i] = RADIX_TABLE[value % radix];                 // generate results
    buffer[rlen + 1] = 0;                                       // make buffer C-style string
    return rlen + 1;
}