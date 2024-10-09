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
 * Функція сортування бульбашкою (Bubble Sort).---------------------------------------------------
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
 * Функція швидкого сортування (QuickSort) за методом Хоара.--------------------------------------------
 * Використовує підхід розділення для сортування масиву.
 * Для малих підмасивів (менше ніж 10 елементів)
 * використовує вставне сортування для підвищення продуктивності.
 * Часова складність: O(n log n) в середньому випадку.
 */
void quickSort(vector<int>& arr, int low, int high) {
    while (low < high) {
        // Якщо кількість елементів в підмасиві менша за поріг, використовуємо insertion sort
        if (high - low < 10) {
            for (int i = low + 1; i <= high; i++) {
                int key = arr[i];
                int j = i - 1;
                while (j >= low && arr[j] > key) {
                    comparisons++;
                    arr[j + 1] = arr[j];
                    exchanges++;
                    j--;
                }
                arr[j + 1] = key;
            }
            break;
        }

        int pivot = arr[low];  // Вибір опорного елемента
        int left = low;
        int right = high;

        while (left < right) {
            // Пошук елементу, меншого за pivot з правого боку
            while (arr[right] >= pivot && left < right) {
                comparisons++;
                right--;
            }
            if (left != right) {
                arr[left] = arr[right];
                exchanges++;
                left++;
            }
            // Пошук елементу, більшого за pivot з лівого боку
            while (arr[left] <= pivot && left < right) {
                comparisons++;
                left++;
            }
            if (left != right) {
                arr[right] = arr[left];
                exchanges++;
                right--;
            }
        }
        arr[left] = pivot;  // Вставка опорного елемента на правильну позицію
        exchanges++;

        // Сортуємо менший підмасив рекурсивно, а більший ітеративно
        if (left - low < high - left) {
            quickSort(arr, low, left - 1);
            low = left + 1;
        }
        else {
            quickSort(arr, left + 1, high);
            high = left - 1;
        }
    }
}

/**
 * Функція сортування Шелла (Shell Sort).------------------------------------------------
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
void fillBestCase(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = i;
    }
}

/**
 * Функція для заповнення масиву у найгіршому випадку.
 * Заповнює масив з відсортованими елементами у зворотному порядку
 * (від n-1 до 0).
 */
void fillWorstCase(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = arr.size() - i;
    }
}

/**
 * Функція для заповнення масиву випадковими значеннями.
 * Генерує випадкові числа до maxValue для кожного елемента масиву.
 */
void fillRandomCase(vector<int>& arr, int maxValue) {
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

/**
 * Основна функція програми.
 * Використовує різні методи сортування на масивах різних розмірів
 * та випадкових значень, а також виводить результати у таблиці.
 */
int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    srand(time(0));
    const int sizes[] = { 1000, 10000, 20000 };  // Розміри масивів для тестування

    for (int n : sizes) {
        vector<int> arr(n);

        // Таблиця для Bubble Sort
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

        // Таблиця для QuickSort
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

        // Таблиця для Shell Sort
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
    }

    return 0;
}

// Оптимізована функція швидкого сортування (QuickSort) з використанням вставок для малих підмасивів
// Використання рекурсії для меншого підмасиву, а ітерації — для більшого

// Функція для заповнення масиву у найкращому випадку (вже відсортований)

// Функція для заповнення масиву у найгіршому випадку (відсортований у зворотному порядку)

// Функція для заповнення масиву випадковими значеннями