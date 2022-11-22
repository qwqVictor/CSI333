/**
 * Author: Huang Kaisheng <2020215138@stu.cqupt.edu.cn>
 * Description: entry source
 * Version: 2022/11/21
 */
#include "main.h"

static char* argv0;
int main(int argc, char const *argv[]) {
    argv0 = hks_basename(argv[0]);
    if (!strncmp(argv0, MODE_COPY_ARGV0, sizeof(MODE_COPY_ARGV0) - 1)) {
        return copy_main(argc, argv);
    }
    if (!strncmp(argv0, MODE_MOVE_ARGV0, sizeof(MODE_MOVE_ARGV0) - 1)) {
        return move_main(argc, argv);
    }
}