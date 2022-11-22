/**
 * Author: Huang Kaisheng <2020215138@stu.cqupt.edu.cn>
 * Description: utility functions header
 * Version: 2022/11/22
 */
#ifndef HUANGKAISHENG_UTIL_H
#define HUANGKAISHENG_UTIL_H
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define hks_errorf(template, ...) (fprintf(stderr, "%s: " template "\n", argv0, ##__VA_ARGS__))
#define hks_perror() (perror(argv0))

#ifndef PATH_MAX
#define PATH_MAX (pathconf("/", _PC_PATH_MAX))
#endif

char* hks_basename(const char* path);
unsigned char hks_ask_for_overwrite(const char* path);

#endif // !HUANGKAISHENG_UTIL_H