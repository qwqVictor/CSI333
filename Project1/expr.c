/**
 * Author: Huang Kaisheng <2020215138@stu.cqupt.edu.cn>
 * Description: Implementation of expression evaluation
 * Version: 2022/10/07
 */

#include "expr.h"
int eval_expr(const char* expr, const int len) {
    int lvalue = 0, rvalue = 0;
    char op = '+';                                  // set initial operation to add for first number
    for (int i = 0; i < len; i++) {
        if (expr[i] == ' ') continue;
        if (expr[i] >= '0' && expr[i] <= '9') {
            rvalue = rvalue * 10 + (expr[i] - '0'); // right value atoi
            if (i != len - 1)                       // if not terminated, skip calculation for number index
                continue;
        }
        switch (op) {                               // do calculation
        case '+':
            lvalue += rvalue;
            break;
        case '-':
            lvalue -= rvalue;
            break;
        case '*':
            lvalue *= rvalue;
            break;
        case '/':
            lvalue /= rvalue;
            break;
        default:
            break;
        }
        rvalue = 0, op = expr[i];                   // reset values
    }
    return lvalue;
}