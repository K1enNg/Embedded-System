#include <stdio.h>
#include "swapTwoIntegers.c"
#include "sumAllElements.c"
#include "reverseAnArray.c"

int main() {
    int *p; //pointer to integer
    char *po; //pointer to character
    double *p1; // pointer to double

    int a;
    a = 10;
    p = &a; // &a = address of a

    printf("Address of p is: %d\n", p);
    printf("Value at p is: %d\n", *p); // *p value at address pointed by p


    printf("%d\n", a);
    *p = 12; //dereferencing
    printf("a = %d\n", a);

    int b = 20;
    *p = b;
    printf("Address of p is now: %d\n", p);
    printf("Value at p is now: %d\n", *p);


    // swap 2 integers
    int x = 10, y = 20;
    swap(&x, &y);
    printf("x = %d, y = %d\n", x, y);

    //sum all elements of an array
    int arr[] = {1, 2, 3, 4, 5};
    printf("sum = %d\n", sumArray(arr,5));

    //reverse an array
    int arr1[] = {2, 5, 7, 12, 9};
    printf("reverse = %d\n", reverse(arr1, 5));

    return 0;
}



