/**
 * Author: Huang Kaisheng <2020215138@stu.cqupt.edu.cn>
 * Description: utility functions implementation
 * Version: 2022/11/22
 */
#include "util.h"

void hks_perror(const char* message) {
    fprintf(stderr, "%s: %s", argv0, message);
}

void hks_perror() {
    perror(argv0);
}