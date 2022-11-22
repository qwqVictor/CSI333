/**
 * Author: Huang Kaisheng <2020215138@stu.cqupt.edu.cn>
 * Description: copy function definition
 * Version: 2022/11/22
 */
#ifndef HUANGKAISHENG_COPY_H
#define HUANGKAISHENG_COPY_H
#include "util.h"

int copy_file_to_file(char const src_file[], char const dest_file[], struct stat* const src_stat, const char* argv0);
int copy_files_to_dir(int src_count, char const* src[], char const dest[], const char* argv0);
int copy_main(int argc, char const* argv[]);

#endif // !HUANGKAISHENG_COPY_H