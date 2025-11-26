int array_get_min(int array[], int array_len) {
    int min = 0;

    for (int i = 1; i < array_len; i++) {
        if (array[i] < array[min]) {
            min = i;
        }
    }

    return array[min];
}

int array_get_max(int array[], int array_len) {
    int max = 0;

    for (int i = 1; i < array_len; i++) {
        if (array[i] > array[max]) {
            max = i;
        }
    }

    return array[max];
}

int array_count_value(int array[], int array_len, int value) {
    int count = 0;
    for (int i = 0; i < array_len; i++) {
        if (array[i] == value) {
            count++;
        }
    }

    return count;
}
