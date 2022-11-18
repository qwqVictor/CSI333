#include <stdio.h>
#include <ctype.h>

int main(int argc, char const *argv[]) {
    if (argc < 2)
        return 1;
    FILE* f = fopen(argv[1], "r");
    if (f == NULL) {
        return 2;
    }
    for (char ch = fgetc(f); ch != EOF;) {
        if (isspace(ch)) {
            while (isspace((ch = fgetc(f))) && ch != EOF);
            putchar('\n');
        }
        else {
            putchar(ch);
            ch = fgetc(f);
        }
    }
    return 0;
}