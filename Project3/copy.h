/**
 * Author: Huang Kaisheng <2020215138@stu.cqupt.edu.cn>
 * Description: copy function definition
 * Version: 2022/11/22
 */
#ifndef HUANGKAISHENG_COPY_H
#define HUANGKAISHENG_COPY_H
#include "util.h"

int copy_file_to_file(char const src_file[], int src_pathfd, char const dest_file[], int dest_pathfd, struct stat* src_stat, const char* argv0);
int copy_file_to_dir(char const src_file[], int src_pathfd, char const dest_file[], int dest_pathfd, const char* argv0);

int copy_main(int argc, char const* argv[]);

#endif // !HUANGKAISHENG_COPY_H