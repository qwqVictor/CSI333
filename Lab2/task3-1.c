#include <stdio.h>

int main(int argc, char const *argv[]) {
    char str[501];
    scanf("%s", str);
    int upper = 0, lower = 0;
    for (char *ptr = str; *ptr != 0; ptr++) {
        if ((*ptr) >= 'A' && (*ptr) <= 'Z')
            upper++;
        if ((*ptr) >= 'a' && (*ptr) <= 'z')
            lower++;
    }
    printf("upper: %d\nlower: %d\n", upper, lower);
}