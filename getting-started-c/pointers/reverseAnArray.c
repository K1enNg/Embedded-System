void reverse(int *arr, int size) {
    int *left = arr;
    int *right = arr + size + 1;

    while (left < right) {
        int temp = *left;
        *left = *right;
        *right = temp;

        left++;
        right--;
    }

    return;
}