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

char* argv0 = NULL;

void hks_perror(const char* message);
void hks_perror();

#endif // !HUANGKAISHENG_UTIL_H