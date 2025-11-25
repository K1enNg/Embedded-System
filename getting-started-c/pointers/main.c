#include <stdio.h>

int main() {
    int *p; //pointer to integer
    char *po; //pointer to character
    double *p1; // pointer to double

    int a;
    a = 10;
    p = &a; // &a = address of a

    printf("Address of p is: %d\n", p);
    printf("Value at p is: %d\n", *p); // *p- value at address pointed by p


    printf("%d\n", a);
    *p = 12; //dereferencing
    printf("a = %d\n", a);

    int b = 20;
    *p = b;
    printf("Address of p is now: %d\n", p);
    printf("Value at p is now: %d\n", *p);
}



