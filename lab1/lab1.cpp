//number of variant - 10
//Illarionov Mykyta

// Користувач вводить число n. Визначити  факторіал числа n (n!).
// Факторіал n вираховуються як добуток натуральних чисел від 1 до n;    n!=1 * 2 * 3 *…* n;    0!=1; 
#include <iostream>
#include <windows.h>
using namespace std;

long long factorial(int n) {
    if (n == 0) return 1;

    long long result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);


    int n;
    cout << "Input value of n(but only >0): ";
    cin >> n;

    if (n < 0) {
        cout << "Factorial is defined only for non-negative integers." << endl;
    }
    else {
        cout << "The factorial of " << n << " is: " << factorial(n) << endl;
    }

    return 0;
}