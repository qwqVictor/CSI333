/**
 * Author: Huang Kaisheng <2020215138@stu.cqupt.edu.cn>
 * Description: utility functions implementation
 * Version: 2022/11/22
 */
#include "util.h"

char* hks_basename(const char* path) {
    char* rchr = strrchr(path, '/');
    return (rchr == NULL) ? path : rchr + 1;
}

unsigned char hks_ask_for_overwrite(const char* path) {
    FILE* fp = fopen("/dev/tty", "rw");
    if (fp == NULL)
        return 0;
    fprintf(fp, "Path '%s' exists. Overwrite? [y/n]", path);
    int c = fgetc(fp);
    fclose(fp);
    return c == 'y';
}