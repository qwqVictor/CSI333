/**
 * Author: Huang Kaisheng <2020215138@stu.cqupt.edu.cn>
 * Description: move function implementation
 * Version: 2022/11/22
 */
#include "move.h"
#include "copy.h"
static char* argv0 = "move";

int move_file(char const src_file[], int src_pathfd, char const dest_file[], int dest_pathfd, const char* argv0) {
    struct stat src_stat;
    bool internally_opened_fd = false;
    if (dest_pathfd == -1) {
        hks_perror();
        return -1;
    }
    // stat the source file
    if (fstatat(src_pathfd, src_file, &src_stat, AT_SYMLINK_NOFOLLOW) >= 0) {
        switch (src_stat.st_mode & S_IFMT) {
        // if source file is a regular file
        case S_IFREG:
        case S_IFLNK:
        HARDLINKAT:
            if (linkat(src_pathfd, src_file, dest_pathfd, dest_file, 0) < 0) {
                switch (errno) {
                case EEXIST:
                    // if exists, first ask to overwrite
                    if (hks_ask_for_overwrite(dest_file)) {
                        if (unlinkat(dest_pathfd, dest_file, 0) < 0) {
                            hks_perror();
                            return -1;
                        }
                        // after unlinked, go back and link again
                        goto HARDLINKAT;
                    }
                    break;
                case EXDEV:
                    // if cross device link encountered, copy it manually.
                    if (copy_file_to_dir(src_file, src_pathfd, dest_file, dest_pathfd, argv0) == -1) {
                        hks_perror();
                        return -1;
                    }
                    break;
                default:
                    hks_perror();
                    return -1;
                }
            }
            if (unlinkat(src_pathfd, src_file, 0) != -1) {
                return 0;
            } else {
                hks_perror();
                return -1;
            }
            break;
        case S_IFDIR:
            hks_errorf("unsupported for directory");
            break;
        default:

            break;
        }
    } else {
        internally_opened_fd ? close(dest_pathfd) : 0;
        hks_perror();
        return -1;
    }
    return 1;
}

int move_files_to_dir(int src_count, char const* src[], char const dest[], const char* argv0) {
    // for each source files
    struct stat dest_stat;
    for (int i = 0; i < src_count; i++) {
        const char* src_file = src[i];
        if (stat(dest, &dest_stat) != -1) {
            if (src_count > 1 && !S_ISDIR(dest_stat.st_mode)) {
                hks_errorf("destination %s must be a directory when multiple sources");
                return 1;
            }
            if (S_ISDIR(dest_stat.st_mode)) {
                int dest_fd = open(dest, O_RDONLY | O_DIRECTORY);
                if (dest_fd != -1) {
                    if (move_file(src_file, AT_FDCWD, hks_basename(src_file), dest_fd, argv0) != -1) {
                    } else {
                        close(dest_fd);
                        hks_perror();
                        return -1;
                    }
                    close(dest_fd);
                }
            }
            else
                move_file(src_file, AT_FDCWD, dest, AT_FDCWD, argv0);
        } else {
            if (errno == ENOENT) {
                if (src_count > 1) {
                    hks_errorf("destination %s not exist");
                    return 1;
                } else {
                    struct stat src_stat;
                    if (lstat(src_file, &src_stat) != -1) {
                        if (S_ISDIR(src_stat.st_mode)) {
                            if (mkdirat(AT_FDCWD, dest, src_stat.st_mode & 0777) != -1) {
                                int dest_fd = open(dest, O_RDONLY | O_DIRECTORY);
                                if (dest_fd != -1) {
                                    if (move_file(src_file, AT_FDCWD, hks_basename(src_file), dest_fd, argv0) != -1) {
                                    } else {
                                        close(dest_fd);
                                        hks_perror();
                                        return -1;
                                    }
                                } else {
                                    hks_perror();
                                    return -1;
                                }
                            } else {
                                hks_perror();
                                return -1;
                            }
                        } else
                            move_file(src_file, AT_FDCWD, dest, AT_FDCWD, argv0);
                    } else {
                        hks_perror();
                        return -1;
                    }
                }
            } else {
                hks_perror();
                return -1;
            }
        }
    }
}

int move_main(int argc, char const* argv[]) {
    const char* argv0 = "move";
    move_files_to_dir(argc - 2, argv + 1, argv[(argc - 1)], argv0);
}