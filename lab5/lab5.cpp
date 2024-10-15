#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>   // Для rand()
#include <ctime>     // Для time()
#include <iomanip>   // Для setw і форматування таблиці
#include <windows.h>
using namespace std;

// Глобальні змінні для підрахунку кількості порівнянь та обмінів
int comparisons = 0;
int exchanges = 0;

/**
 * Скидає лічильники порівнянь та обмінів до нуля.
 * Використовується перед запуском кожного алгоритму сортування
 * для отримання точних результатів.
 */
void resetCounters() {
    comparisons = 0;
    exchanges = 0;
}

/**
 * Функція сортування бульбашкою (Bubble Sort).---------------------------------------------------   Bubble Sort
 * Реалізує алгоритм бульбашкового сорту, який проходить
 * через масив, порівнює сусідні елементи і обмінює їх,
 * якщо вони не в правильному порядку.
 * Часова складність: O(n^2) в найгіршому випадку.
 */
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                exchanges++;
            }
        }
    }
}

/**
 * Функція швидкого сортування (QuickSort) за методом Хоара.--------------------------------------------  QuickSort
 * Використовує підхід розділення для сортування масиву.
 * Для малих підмасивів (менше ніж 10 елементів)
 * використовує вставне сортування для підвищення продуктивності.
 * Часова складність: O(n log n) в середньому випадку.
 */

// Функція для розділення масиву
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];  // Вибираємо останній елемент як опорний
    int i = low - 1;  // Індекс для елементів, менших за pivot

    for (int j = low; j <= high - 1; j++) {
        comparisons++;  // Лічимо порівняння
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);  // Обмін елементів
            exchanges++;  // Лічимо обміни
        }
    }

    swap(arr[i + 1], arr[high]);  // Встановлюємо pivot на правильну позицію
    exchanges++;  // Лічимо обміни
    return i + 1;  // Повертаємо індекс опорного елемента
}

// Реалізація функції швидкого сорту
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);  // Отримуємо позицію опорного елемента

        // Рекурсивні виклики для підмасивів
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}





/**
 * Функція сортування Шелла (Shell Sort).------------------------------------------------    Shell Sort
 * Реалізує алгоритм сортування Шелла, який базується на
 * порівнянні та обміні елементів на різних відстанях
 * (gap), що зменшуються з кожною ітерацією.
 * Часова складність: O(n^(3/2)) в середньому випадку.
 */
void shellSort(vector<int>& arr) {
    int n = arr.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                comparisons++;
                arr[j] = arr[j - gap];
                exchanges++;
            }
            arr[j] = temp;
        }
    }
}

/**
 * Функція для заповнення масиву у найкращому випадку.
 * Заповнює масив з відсортованими елементами (від 0 до n-1).
 */
void fillBestCase(vector<int>& arr) {//========================================       BEST
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = i;
    }
}

/**
 * Функція для заповнення масиву у найгіршому випадку.
 * Заповнює масив з відсортованими елементами у зворотному порядку
 * (від n-1 до 0).
 */



void fillWorstCase(vector<int>& arr) {//==========================================        WORST
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = arr.size() - i - 1;  // від n-1 до 0
    }
}


//void fillWorstCase(vector<int>& arr) {
//    for (int i = arr.size() - 1; i >= 0; i--) {
//        arr[i] = i;  // від n-1 до 0
//    }
//}

/**
 * Функція для заповнення масиву випадковими значеннями.
 * Генерує випадкові числа до maxValue для кожного елемента масиву.
 */
void fillRandomCase(vector<int>& arr, int maxValue) {//===============================     RANDOM
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = rand() % maxValue;
    }
}

/**
 * Функція для виведення заголовка таблиці з результатами.
 * Виводить заголовок таблиці для кожного методу сортування
 * з вказанням кількості елементів.
 */
void printTableHeader(const string& methodName, int n) {
    cout << "\n\n===============================" << endl;
    cout << "   " << methodName << " Results (N = " << n << ")" << endl;
    cout << "===============================" << endl;
    cout << "|   Case   | Comparisons | Exchanges |" << endl;
    cout << "--------------------------------------" << endl;
    cout.flush();  // Очищаємо потік виведення
}

/**
 * Функція для виведення рядка з результатами.
 * Виводить кількість порівнянь та обмінів для кожного випадку
 * (найкращий, середній, найгірший).
 */
void printTableRow(const string& caseName) {
    cout << "| " << setw(8) << caseName << " | "
        << setw(11) << comparisons << " | "
        << setw(9) << exchanges << " |" << endl;
    cout.flush();  // Очищаємо потік виведення
}

void printingAllArrays(const vector<int>& arr, const string& arrayName) {
    cout << "\n\n\n" << arrayName << ": --[ \n";
    for (int i = 0; i < arr.size(); i++) {
        cout << setw(4) << arr[i] << " ";
    }
    cout << "\n]--" << endl;
}






/**
 * Основна функція програми.
 * Використовує різні методи сортування на масивах різних розмірів
 * та випадкових значень, а також виводить результати у таблиці.
 */
int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    srand(time(0));


    const int sizes[] = { 10, 100, 200 };  // Розміри масивів для тестування
    //const int sizes[] = { 1000, 10000, 100000 };

    for (int n : sizes) {//виведення початкового, ще не посортованого масиву, для подальшого порівняння. Окремий цикл фор для зрозумілості

        vector<int> arr(n);

        // Заповнення масиву випадковими значеннями
        fillRandomCase(arr, n);

        cout << "\n\n===============================\n";
        cout << "   Arrays Before Sorting (N = " << n << ")\n";
        cout << "===============================\n";

        // Виведення масиву перед сортуванням
        printingAllArrays(arr, "Random Array");

        cout << "--------------------------------------" << endl;
        Sleep(50); // Затримка
    }

    

    for (int n : sizes) {//перебирання елементів масиву не зважаючи на індекси
        vector<int> arr(n);

        //Sorting
        cout << "\n\n===============================================\n";
        cout << "\t\t\t\t\tSORTING\n";
        cout << "===============================================\n";

        // -------------------------------------------------Таблиця для Bubble Sort
        printTableHeader("Bubble Sort", n);

        fillBestCase(arr);
        resetCounters();
        bubbleSort(arr);
        printTableRow("Best");

        fillRandomCase(arr, n);
        resetCounters();
        bubbleSort(arr);
        printTableRow("Average");

        fillWorstCase(arr);
        resetCounters();
        bubbleSort(arr);
        printTableRow("Worst");

        cout << "--------------------------------------" << endl;
        Sleep(50);  // Затримка

        // ---------------------------------------------------------Таблиця для QuickSort
        printTableHeader("QuickSort", n);

        fillBestCase(arr);
        resetCounters();
        quickSort(arr, 0, n - 1);
        printTableRow("Best");

        fillRandomCase(arr, n);
        resetCounters();
        quickSort(arr, 0, n - 1);
        printTableRow("Average");

        fillWorstCase(arr);
        resetCounters();
        quickSort(arr, 0, n - 1);
        printTableRow("Worst");

        cout << "--------------------------------------" << endl;
        Sleep(50);  // Затримка

        // --------------------------------------------------------Таблиця для Shell Sort
        printTableHeader("Shell Sort", n);

        fillBestCase(arr);
        resetCounters();
        shellSort(arr);
        printTableRow("Best");

        fillRandomCase(arr, n);
        resetCounters();
        shellSort(arr);
        printTableRow("Average");

        fillWorstCase(arr);
        resetCounters();
        shellSort(arr);
        printTableRow("Worst");

        cout << "--------------------------------------" << endl;
        Sleep(50);  // Затримка



        // Вивести масиви після таблиць
        cout << "\n\n===============================\n";
        cout << "   Arrays After Sorting (N = " << n << ")\n";
        cout << "===============================\n";

        printingAllArrays(arr, "Bubble Sort Array");

        

        printingAllArrays(arr, "Quick Sort Array");

        

        printingAllArrays(arr, "Shell Sort Array");

        cout << "--------------------------------------" << endl;
        Sleep(50);
    }


   


    return 0;
}

