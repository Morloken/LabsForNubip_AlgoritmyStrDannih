//1)           10. Згенерувати і вивести на екран масив з 10 випадкових чисел від  -140 до 140, та сформувати інший масив з елементів масиву, які більше 30. 


// #include <iostream>
// #include <ctime>
// #include <cstdlib>

// using namespace std;

// int main() {
//     // --------------------------------------
//     srand(static_cast<unsigned int>(time(nullptr)));
//   /*
//   Залишив static_cast, оскільки він чітко вказує на те, що я здійснюю явне приведення типу. Це допомагає уникнути проблем із неявним приведенням типів
//   */
//     // --------------------------------------
//     const int size = 10;
//     int array[size];
//     int greater_than_30[size]; // >30
//     int count = 0; // для відстеження кількості елементів, більших за 30

//     // ------------------------------------------
//     cout << "Масив з випадкових чисел:\n";
//     for (int i = 0; i < size; ++i) {
//         array[i] = rand() % 281 - 140; 
//         cout << array[i] << " ";
//         if (array[i] > 30) {
//             greater_than_30[count] = array[i]; // Зберігаємо елементи, більші за 30
//             count++; 
//         }
//     }
//     cout << "\n-------------------" << endl;
//     //------------------------------------------
//     cout << "\nМасив з елементів, більших за 30:\n";
//     if (count == 0) {
//         cout << "Немає елементів, більших за 30\n"; 
//     } else {
//         for (int i = 0; i < count; ++i) {
//             cout << greater_than_30[i] << " "; // Вивід > 30
//         }
//         cout << endl;
//     }

//     return 0;
// }


//2)         10. Ввести квадратну матрицю. Знайти суму елементів тих рядків, у яких на головній діагоналі знаходяться від’ємні числа. 
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip> // для setw()
#include <vector>  // для std::vector

using namespace std;

int main() {

    srand(static_cast<unsigned int>(time(nullptr)));

    //------------------------------------------
    int size;
    cout << "Введіть розмір квадратної матриці: ";
    cin >> size;

    //------------------------------------------
    // Використання векторів замість статичного масиву
    vector<vector<int>> matrix(size, vector<int>(size));

    cout << "\nМатриця:\n";
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = rand() % 201 - 100; // Випадкове значення в діапазоні [-100, 100]
            cout << setw(5) << matrix[i][j]; // Виведення з шириною поля 5
        }
        cout << endl;
    }

    int sum = 0;
    cout << "\nРядки, де на головній діагоналі є від'ємні числа:\n";

    // Перевірка головної діагоналі і підрахунок суми рядків з від'ємними елементами на діагоналі
    for (int i = 0; i < size; ++i) {
        if (matrix[i][i] < 0) {
            int rowSum = 0;
            cout << "Рядок " << i + 1 << ": ";
            for (int j = 0; j < size; ++j) {
                rowSum += matrix[i][j];
                cout << setw(5) << matrix[i][j]; // Виведення з шириною поля 5
            }
            sum += rowSum;
            cout << " | Сума рядка: " << rowSum << endl;
        }
    }

    cout << "\nЗагальна сума елементів рядків, де на головній діагоналі від'ємні числа: " << sum << endl;

    return 0;
}
