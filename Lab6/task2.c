#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

int main(int argc, char const *argv[]) {
    uint8_t numbers[100];
    uint16_t sum = 0;
    char buffer[20];
    srand(time(NULL));
    for (size_t i = 0; i < 100; i++) {
        numbers[i] = rand() % 100;
        sum += numbers[i];
    }
    printf("The sum: %hu\n", sum);
    sprintf(buffer, "numbers.%hu", sum);
    int fd = open(buffer, O_WRONLY | O_TRUNC | O_CREAT, 0644);
    if (fd != -1) {
        for (size_t i = 0; i < 100; i++) {
            sprintf(buffer, "%hhu\n", numbers[i]);
            write(fd, buffer, strlen(buffer));
        }
    }
    else {
        perror("Error");
    }
    close(fd);
    return 0;
}


