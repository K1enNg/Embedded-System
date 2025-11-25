int sumArray(int *arr, int size) {
    int sum = 0;
    int *ptr = arr;

    for (int i = 0; i < size; i++) {
        sum += *(ptr + i);
    }

    return sum;
}