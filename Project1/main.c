/**
 * Author: Huang Kaisheng <2020215138@stu.cqupt.edu.cn>
 * Description: Entrypoint of program
 * Version: 2022/10/07
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "expr.h"
#include "radix.h"

int main(int argc, char const *argv[]) {
    char expr[80 + 1], *result;
    int radix;
    fgets(expr, 80, stdin);
    int value = eval_expr(expr, strlen(expr));
    printf("Value = %d\n", value); fflush(stdout);
    printf("Enter radix: "); fflush(stdout);
    scanf("%d", &radix);
    int rlen = calc_rlen(value, radix);
    result = (char*)malloc(rlen);
    int ret = radix_conv(value, radix, result, rlen);
    puts(result); fflush(stdout);
    free((void*)result);
    return 0;
}