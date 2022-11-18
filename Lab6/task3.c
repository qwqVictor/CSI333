#include <dirent.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

void processNumberFiles(const char* filename) {
    int fd = open(filename, O_RDONLY);
    if (fd != -1) {
        char buffer[BUFSIZ];
        uint8_t numbers[100];
        uint16_t sum = 0;
        size_t index = 0, readsize = 0;
        memset(numbers, 0, sizeof(numbers));
        while ((readsize = read(fd, buffer, BUFSIZ)) > 0) {
            for (size_t i = 0; i < readsize; i++) {
                if (buffer[i] >= '0' && buffer[i] <= '9') {
                    numbers[index] *= 10;
                    numbers[index] += buffer[i] - '0';
                }
                else if (buffer[i] == '\n') index++;
            }
        }
        if (readsize == -1) {
            perror("Error reading");
            close(fd);
            return;
        }
        for (size_t i = 0; i < 100; i++)
            sum += numbers[i];
        printf("Filename: '%s'\t---\tSum: %hu\n", filename, sum);
        close(fd);
    }
    else {
        perror("Error");
        return;
    }
}

int main(int argc, char const* argv[]) {
    DIR* cwd = opendir("./");
    struct dirent* dirContent = NULL;
    while ((dirContent = readdir(cwd)) != NULL) {
#define TASK3_PREFIX ("numbers.")
        if (strncmp(TASK3_PREFIX, dirContent->d_name, sizeof(TASK3_PREFIX) - 1) == 0) {
#undef TASK3_PREFIX
            processNumberFiles(dirContent->d_name);
        }
    }
    return 0;
}
