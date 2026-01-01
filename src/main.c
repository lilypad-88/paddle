#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "array.h"
#include "img.h"

int main() {
    test();
    return 0;

    srand(time(NULL));

    int array_size = 10;
    int array[array_size];

    // Randomize array
    for (int i = 0; i < array_size; i++) {
        array[i] = rand() % 256;
    }

    // Print Array
    for (int i = 0; i < array_size; i++) {
        printf("Array[%d] = %d\n", i, array[i]);
    }

    printf("Min: %d\n", array_get_min(array, array_size));
    printf("Max: %d\n", array_get_max(array, array_size));
    printf("Occurances of 1: %d\n", array_count_value(array, array_size, 1));

    return 0;
}
