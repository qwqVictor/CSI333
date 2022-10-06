#include <stdio.h>
#define debug() (printf("a = %d, b = %d, p = %p\n", a, b, p))
int main() {
    int a = 0, b = 1;
    int* p = &a;
    debug();
    *p = 2;
    debug();
    p = &b;
    debug();
    *p = 3;
    debug();
}