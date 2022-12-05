/**
 * Author: Huang Kaisheng <2020215138@stu.cqupt.edu.cn>
 * Description: copy function implementation
 * Version: 2022/11/22
 */
#include "copy.h"

int copy_file_to_file(char const src_file[], int src_pathfd, char const dest_file[], int dest_pathfd, struct stat* src_stat, const char* argv0) {
    char buffer[BUFSIZ], link_src[PATH_MAX];
    // first try to make hard links
    if (src_stat == NULL) {
        struct stat tmp;
        src_stat = &tmp;
    }
    if (fstatat(src_pathfd, src_file, src_stat, AT_SYMLINK_NOFOLLOW) >= 0) {
        if (S_ISLNK(src_stat->st_mode)) {
            if (readlink(src_file, link_src, PATH_MAX) < 0) {
                hks_perror();
                return -1;
            }
        SYMBOLINKAT:
            if (symlinkat(link_src, dest_pathfd, dest_file) < 0) {
                if (errno == EEXIST) {
                    // if exists, first ask to overwrite
                    if (hks_ask_for_overwrite(dest_file)) {
                        if (unlinkat(dest_pathfd, dest_file, 0) < 0) {
                            hks_perror();
                            return -1;
                        }
                        // after unlinked, go back and link again
                        goto SYMBOLINKAT;
                    }
                } else {
                    hks_perror();
                    return -1;
                }
            }
        } else {
            int src_fd = openat(src_pathfd, src_file, O_RDONLY);
            if (src_fd == -1) {
                hks_perror();
                return -1;
            }
            int dest_fd = openat(dest_pathfd, dest_file, O_WRONLY | O_TRUNC | O_CREAT, src_stat->st_mode & 0777);
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
        }
        return 1;
    } else {
        hks_perror();
        return -1;
    }
}

int copy_file_to_dir(char const src_file[], int src_pathfd, char const dest_file[], int dest_pathfd, const char* argv0) {
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
            if (copy_file_to_file(src_file, AT_FDCWD, hks_basename(src_file), dest_pathfd, &src_stat, argv0) == -1) {
                internally_opened_fd ? close(dest_pathfd) : 0;
                return -1;
            }
            break;
        case S_IFDIR:
            int src_dirfd = openat(src_pathfd, src_file, O_RDONLY | O_DIRECTORY);
            DIR* src_dir = fdopendir(src_file);
            if (src_dir == NULL) {
                hks_perror();
                internally_opened_fd ? close(dest_pathfd) : 0;
                close(src_dirfd);
                return -1;
            }
            
            struct dirent* dir_content = NULL;
            while ((dir_content = readdir(src_dir)) != NULL) {
                if (dir_content->d_type == DT_DIR) {
                    struct stat dest_stat;
                RETRY_DIRCOPY:
                    if (fstatat(dest_pathfd, dir_content->d_name, &dest_stat, AT_SYMLINK_NOFOLLOW) != -1) {
                        int dest_dir_fd = openat(dest_pathfd, dir_content->d_name, O_RDONLY | O_DIRECTORY);
                        if (dest_dir_fd != -1) {
                            copy_file_to_dir(dir_content->d_name, dirfd(src_dir), dir_content->d_name, dest_dir_fd, argv0);
                            close(dest_dir_fd);
                        }
                        else {
                            hks_perror();
                            internally_opened_fd ? close(dest_pathfd) : 0;
                            close(src_dirfd);
                            return -1;
                        }
                    } else {
                        if (errno == ENOENT) {
                            if (mkdirat(dest_pathfd, dir_content->d_name, src_stat.st_mode & 0777) != -1) {
                                goto RETRY_DIRCOPY;
                            }
                            hks_perror();
                            internally_opened_fd ? close(dest_pathfd) : 0;
                            close(src_dirfd);
                            return -1;
                        }
                    }
                }
                else {
                    copy_file_to_dir(dir_content->d_name, dirfd(src_dir), dir_content->d_name, dest_pathfd, argv0);
                }
            }

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

int copy_files_to_dir(int src_count, char const* src[], char const dest[], const char* argv0) {
    // for each source files
    struct stat dest_stat;
    for (int i = 0; i < src_count; i++) {
        const char* src_file = src[i];
        if (stat(dest, &dest_stat) != -1) {
            if (src_count > 1 && !S_ISDIR(dest_stat.st_mode)) {
                hks_errorf("destination %s must be a directory when multiple sources");
                return 1;
            }
            int dest_fd = open(dest, O_RDONLY | O_DIRECTORY);
            if (dest_fd != -1) {
                if (copy_file_to_dir(src_file, AT_FDCWD, hks_basename(src_file), dest_fd, argv0) != -1) {
                } else {
                    close(dest_fd);
                    hks_perror();
                    return -1;
                }
                close(dest_fd);
            }
        }
        else {
            if (errno == ENOENT) {
                if (src_count > 1) {
                    hks_errorf("destination %s not exist");
                    return 1;
                }
                else {
                    struct stat src_stat;
                    if (lstat(src_file, &src_stat) != -1) {
                        if (S_ISDIR(src_stat.st_mode)) {
                            if (mkdirat(AT_FDCWD, dest, src_stat.st_mode & 0777) != -1) {
                                int dest_fd = open(dest, O_RDONLY | O_DIRECTORY);
                                if (dest_fd != -1) {
                                    if (copy_file_to_dir(src_file, AT_FDCWD, hks_basename(src_file), dest_fd, argv0) != -1) {
                                    } else {
                                        close(dest_fd);
                                        hks_perror();
                                        return -1;
                                    }
                                }
                                else {
                                    hks_perror();
                                    return -1;
                                }
                            }
                            else {
                                hks_perror();
                                return -1;
                            }
                        }
                        else copy_file_to_file(src_file, AT_FDCWD, dest, AT_FDCWD, &src_stat, argv0);
                    }
                    else {
                        hks_perror();
                        return -1;
                    }
                }
            }
            else {
                hks_perror();
                return -1;
            }
        }
    }
}

int copy_main(int argc, char const* argv[]) {
    const char* argv0 = "copy";
    copy_files_to_dir(argc - 2, argv + 1, argv[(argc - 1)], argv0);
}