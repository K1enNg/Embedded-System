#include <iostream>
#include "calculator.cpp"

using namespace std;

int main() {
    double x = 0;
    double y = 0;
    double result = 0;
    char oper = '\0';
    cout << "Console calculator";
    cout << "\n";
    cout << "Enter operation (+, -, *, /): ";

    Calculator calc;
    while (true) {
        cin >> x >> oper >> y; //"cin" accepts input from the user
        result = calc.Calculate(x, oper, y);
        cout << result << "\n";
    }
    return 0;
}