/**
 * Author: Huang Kaisheng <2020215138@stu.cqupt.edu.cn>
 * Description: Definition of radix conversion
 * Version: 2022/10/07
 */
#ifndef VICTORHUANG_RADIX
#define VICTORHUANG_RADIX
#include <math.h>

#define INVALID_RADIX_SPECIFIED (-1)
#define BUFFER_LENGTH_OVERFLOW (-2)

/**
 * Calculate radix conversion result string length
 * @param value the value to convert
 * @param radix the target radix
 * @return string length
 */
int calc_rlen(int value, const int radix);

/**
 * Convert number to specified radix
 * @param value  the value to convert
 * @param radix  the target radix
 * @param buffer the buffer to be written
 * @param len    the max length of buffer
 * @return error code
 */
int radix_conv(int value, const int radix, char* buffer, const int len);

#endif