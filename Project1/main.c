#include <stdio.h>
#include <string.h>
#include "expr.h"

int main(int argc, char const *argv[]) {
    char expr[80 + 1];
    fgets(expr, 80, stdin);
    printf("%d\n", eval_expr(expr, strlen(expr)));
}