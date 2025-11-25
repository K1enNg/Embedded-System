#include <iostream>

int main() {
    std::cout <<"Hello World\n"; // std::cout lives in the iostream library

    int x; // definition of variable x
    
    // x = 21;

    int a = 5; //copy-initialization
    int b ( 4 ); //direct-initialization
    

    int c { 7 };   // direct-list-initialization (initial value in braces), preferred
    int d {};      // value-initialization (empty braces)

    [[maybe_unused]] int e = 9; // compiler doesn't warn about unused variables

    std::cout << "Enter an integer: ";

    int num{}; // define variable num as an integer vaiable
    std::cin >> num; // get integer value from user's input

    int doubleNum = num * 2; // define a new var and initialized with num * 2
    std::cout << "Double that number is: " << doubleNum;
    
    return 0;
}