#include <iostream>

int main() {
    std::cout <<"Hello World"; // std::cout lives in the iostream library

    int x; // definition of variable x
    
    // x = 21;

    int a = 5; //copy-initialization
    int b ( 4 ); //direct-initialization
    

    int c { 7 };   // direct-list-initialization (initial value in braces), preferred
    int d {};      // value-initialization (empty braces)

    [[maybe_unused]] int e = 9; // compiler doesn't warn about unused variables
    
    return 0;
}