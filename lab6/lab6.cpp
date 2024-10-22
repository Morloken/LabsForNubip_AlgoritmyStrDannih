//Написати програму на мові С++, яка використовує вказівники, та
//механізм виділення динамічної пам’яті, відповідно варіанту.

//10. Згенерувати і вивести на екран масив з 10 випадкових чисел від
//-140 до 140, та сформувати інший масив з елементів масиву, які більше 30

#include <iostream>
#include <cstdlib>  //  rand() та srand()
#include <ctime>    //  time()
#include <windows.h>
#include <locale> // Для роботи з локалями

using namespace std;

int main() {
    setlocale(LC_ALL, ""); // Встановлення локалі на основі поточного середовища (для підтримки кирилиці)

    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    srand(time(0)); 

    // динамічна пам'ять для масиву з 10 елементів
    int* arr = new int[10];

    // випадкові числа від -140 до 140 і заповнення масиву
    cout << "Масив з 10 випадкових чисел від -140 до 140:\n";
    for (int i = 0; i < 10; ++i) {
        arr[i] = rand() % 281 - 140; 
        cout << arr[i] << " ";
    }
    cout << endl;

    // кількість елементів, які більше 30
    int count = 0;
    for (int i = 0; i < 10; ++i) {
        if (arr[i] > 30) {
            ++count;
        }
    }

    //  динамічна пам'ять для нового масиву
    int* filteredArr = new int[count];

    // Новий масив елементыв, які більше 30
    int j = 0;
    for (int i = 0; i < 10; ++i) {
        if (arr[i] > 30) {
            filteredArr[j++] = arr[i];
        }
    }

    // Вивід нового масиву
    cout << "Масив елементів, які більше 30:\n";
    for (int i = 0; i < count; ++i) {
        cout << filteredArr[i] << " ";
    }
    cout << endl;

    // Очищення динамічної пам'яті
    delete[] arr;
    delete[] filteredArr;

    return 0;
}
