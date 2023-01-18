/**
 * Author: Huang Kaisheng <2020215138@stu.cqupt.edu.cn>
 * Description: Entrypoint of the program
 * Version: 2022/12/19
 */

#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

float average = 0;
int maximum = INT_MIN, minimum = INT_MAX;

void* calc_average(void* args) {
    int* array = ((int*)args) + 1;
    int len = ((int*)args)[0];
    for (int i = 0; i < len; i++) {
        average += array[i];
    }
    average /= len;
    return NULL;
}

void* calc_maximum(void* args) {
    int* array = ((int*)args) + 1;
    int len = ((int*)args)[0];
    for (int i = 0; i < len; i++) {
        maximum = maximum < array[i] ? array[i] : maximum;
    }
    return NULL;
}

void* calc_minimum(void* args) {
    int* array = ((int*)args) + 1;
    int len = ((int*)args)[0];
    for (int i = 0; i < len; i++) {
        minimum = minimum > array[i] ? array[i] : minimum;
    }
    return NULL;
}

int main(int argc, char const *argv[]) {
    int* values = (int*)malloc(argc * sizeof(int));
    values[0] = argc - 1;
    for (int i = 1; i < argc; i++) {
        sscanf(argv[i], "%d", &values[i]);
    }
    pthread_t avgt, maxt, mint;
    if (pthread_create(&avgt, NULL, calc_average, values) || pthread_create(&maxt, NULL, calc_maximum, values) || pthread_create(&mint, NULL, calc_minimum, values)) {
        fprintf(stderr, "Failed to create threads!\n");
        exit(EXIT_FAILURE);
    }
    pthread_join(avgt, NULL);
    pthread_join(maxt, NULL);
    pthread_join(mint, NULL);
    printf("The average value is %f\n", average);
    printf("The maximum value is %d\n", maximum);
    printf("The minimum value is %d\n", minimum);
    free(values);
    return 0;
}
