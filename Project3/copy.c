/**
 * Author: Huang Kaisheng <2020215138@stu.cqupt.edu.cn>
 * Description: copy function implementation
 * Version: 2022/11/22
 */
#include "copy.h"

int copy_file_to_file(char const src_file[], char const dest_file[], struct stat* const src_stat, const char* argv0) {
    char buffer[BUFSIZ], link_src[PATH_MAX];
    // first try to make hard links
    if (S_ISLNK(src_stat->st_mode)) {
        if (readlink(src_file, link_src, PATH_MAX) < 0) {
            hks_perror();
            return -1;
        }
SYMBOLINKAT:
        if (symlinkat(link_src, AT_FDCWD, dest_file) < 0) {
            if (errno == EEXIST) {
                // if exists, first ask to overwrite
                if (hks_ask_for_overwrite(dest_file)) {
                    if (unlinkat(AT_FDCWD, dest_file, 0) < 0) {
                        hks_perror();
                        return -1;
                    }
                    // after unlinked, go back and link again
                    goto SYMBOLINKAT;
                }
            }
            else {
                hks_perror();
                return -1;
            }
        }
    }
    else {
HARDLINKAT:
        if (linkat(AT_FDCWD, src_file, AT_FDCWD, dest_file, 0) < 0) {
            switch (errno) {
            case EEXIST:
                // if exists, first ask to overwrite
                if (hks_ask_for_overwrite(dest_file)) {
                    if (unlinkat(AT_FDCWD, dest_file, 0) < 0) {
                        hks_perror();
                        return -1;
                    }
                    // after unlinked, go back and link again
                    goto HARDLINKAT;
                }
                break;
            case EXDEV:
                // if cross device link encountered, copy it manually.
                int src_fd = open(src_file, O_RDONLY);
                if (src_fd == -1) {
                    hks_perror();
                    return -1;
                }
                int dest_fd = open(dest_file, O_WRONLY | O_TRUNC | O_CREAT, src_stat->st_mode & 0777);
                if (dest_fd == -1) {
                    hks_perror();
                    close(src_fd);
                    return -1;
                }
                // read and write
                int nbytes = 0;
                while ((nbytes = read(src_fd, buffer, BUFSIZ)) > 0) {
                    if (write(dest_fd, buffer, BUFSIZ) == -1) {
                        hks_perror();
                        close(src_fd), close(dest_fd);
                        return -1;
                    }
                }
                if (nbytes == -1) {
                    hks_perror();
                    close(src_fd), close(dest_fd);
                    return -1;
                }
                break;
            default:
                hks_perror();
                return -1;
            }
        }
    }
    return 1;
}

int copy_files_to_dir(int src_count, char const* src[], char const dest[], const char* argv0) {
    // preserve dest file name buffer
    char dest_file[PATH_MAX];
    // for each source files
    for (int i = 0; i < src_count; i++) {
        const char* src_file = src[i];
        struct stat src_stat;
        // stat the source file
        if (lstat(src_file, &src_stat) >= 0) {
            switch (src_stat.st_mode & S_IFMT) {
            // if source file is a regular file
            case S_IFREG:
            case S_IFLNK:
                sprintf(dest_file, "%s/%s", dest, hks_basename(src_file));
                if (copy_file_to_file(src_file, dest_file, &src_stat, argv0) == -1) {
                    return -1;
                }
                break;
            case S_IFDIR:
                
                break;
            default:

                break;
            }
        } else {
            hks_perror();
            return -1;
        }
    }
}

int copy_main(int argc, char const* argv[]) {
    const char* argv0 = "copy";
    /*struct stat dest_stat;
    if (stat(dest, &dest_stat) == -1) {
        hks_perror();
        return -1;
    }
    // if the destination is not a directory, error and quit
    if ((dest_stat.st_mode & S_IFMT) != S_IFDIR) {
        hks_errorf("destination '%s' is not a directory.", dest);
        return -1;
    }*/
    copy_files_to_dir(argc - 2, argv + 1, argv[(argc - 1)], argv0);
}