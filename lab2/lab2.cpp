// // --------------------------------------------
// // proggram without reccursion

// #include <iostream>
// #include <cmath>
// using namespace std;

// double taylor_sin(double x, int n) {
//     double term = x;
//     double sum = x;

//     for (int i = 1; i <= n; ++i) {
//         term *= -x * x / (2 * i * (2 * i + 1));
//         sum += term;
//     }

//     return sum;
// }

// int main() {
//     double x = 4;
//     // cout << "Enter value for x: ";
//     // cin >> x;

//     int n = 10; //Ammount of Teylor`s items

//     double sin_x1 = taylor_sin(x + 1, n);
//     // double sin_x1 = sin(x);
//     double sin_x3 = taylor_sin(x + 3, n);

//     double y = sin_x1 / (sin_x3 * sin_x3);

//     cout << "Result(y): " << y << endl;
//     cout << "Sin(x): " << sin(x) << endl;
//     cout<< "Sum: "<< taylor_sin(x, n) << endl; 

//     return 0;
// }

//--------------------------------------------
//proggram with reccursion


#include <iostream>
#include <cmath>
using namespace std;

double taylor_sin_recursive(double x, int n, int term = 1) {
    if (n == 0) {
        return 0;
    }

    double next_term = -x * x / (2 * term * (2 * term + 1));
    return x + next_term * taylor_sin_recursive(x, n - 1, term + 1);
}

int main() {
    double x = 4;
    // cout << "Enter value for x: ";
    // cin >> x;

    int n = 10; //Ammount of Teylor`s items

    double sin_x1 = taylor_sin_recursive(x + 1, n);
    double sin_x3 = taylor_sin_recursive(x + 3, n);

    double y = sin_x1 / (sin_x3 * sin_x3);

    cout << "Result: " << y << endl;
    cout << "Sin(x): " << sin(x) << endl;
    cout << "Sum: " << taylor_sin_recursive(x, n) << endl;

    return 0;
}