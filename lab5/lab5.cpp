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
//void fillWorstCase(vector<int>& arr) {
//    for (int i = 0; i < arr.size(); i++) {
//        arr[i] = arr.size() - i;
//        //arr[i] = n - i - 1;
//
//    }
//}
void fillWorstCase(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = arr.size() - i - 1;  // від n-1 до 0
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
    const int sizes[] = { 10, 100, 200 };  // Розміри масивів для тестування

    for (int n : sizes) {//перебирання елементів масиву не зважаючи на індекси
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


//=============================================================================================================================================================================================================================================
//#include <iostream>
//#include <vector>
//#include <ctime>
//#include <cstdlib>
//#include <iomanip>
//#include <windows.h>
//
//using namespace std;
//
//// Функції для підрахунку порівнянь та обмінів
//int bubbleSort(vector<int>& arr, int& comparisons, int& swaps) {
//    int n = arr.size();
//    comparisons = swaps = 0;
//    bool swapped;
//    for (int i = 0; i < n - 1; i++) {
//        swapped = false;
//        for (int j = 0; j < n - i - 1; j++) {
//            comparisons++; // Кожне порівняння
//            if (arr[j] > arr[j + 1]) {
//                swap(arr[j], arr[j + 1]);
//                swaps++; // Кожен обмін
//                swapped = true; // Відбувся обмін
//            }
//        }
//        if (!swapped) {
//            break; // Якщо обмінів не було, завершити достроково
//        }
//    }
//    return swaps;
//}
//
//int partition(vector<int>& arr, int low, int high, int& comparisons, int& swaps) {
//    int pivot = arr[high];
//    int i = low - 1;
//
//    for (int j = low; j < high; j++) {
//        comparisons++; // Кожне порівняння
//        if (arr[j] < pivot) {
//            i++;
//            swap(arr[i], arr[j]);
//            swaps++; // Кожен обмін
//        }
//    }
//    swap(arr[i + 1], arr[high]);
//    swaps++; // Обмін з опорним елементом
//    return (i + 1);
//}
//
//void quickSort(vector<int>& arr, int low, int high, int& comparisons, int& swaps) {
//    if (low < high) {
//        int pi = partition(arr, low, high, comparisons, swaps);
//        quickSort(arr, low, pi - 1, comparisons, swaps);
//        quickSort(arr, pi + 1, high, comparisons, swaps);
//    }
//}
//
//void shellSort(vector<int>& arr, int& comparisons, int& swaps) {
//    int n = arr.size();
//    comparisons = swaps = 0;
//    for (int gap = n / 2; gap > 0; gap /= 2) {
//        for (int i = gap; i < n; i++) {
//            int temp = arr[i];
//            int j;
//            comparisons++; // Порівняння для входу в цикл
//            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
//                comparisons++; // Кожне порівняння всередині циклу
//                arr[j] = arr[j - gap];
//                swaps++; // Обмін елементів
//            }
//            arr[j] = temp;
//            swaps++; // Обмін елементів при виході
//        }
//    }
//}
//
//// Функція для заповнення масиву
//void fillArray(vector<int>& arr, int type) {
//    int n = arr.size();
//    if (type == 1) { // Відсортований за зростанням (найкращий випадок)
//        for (int i = 0; i < n; i++) {
//            arr[i] = i;
//        }
//    }
//    else if (type == 2) { // Випадковий масив (середній випадок)
//        srand(time(0));
//        for (int i = 0; i < n; i++) {
//            arr[i] = rand() % 1000;
//        }
//    }
//    else if (type == 3) { // Відсортований за спаданням (найгірший випадок)
//        for (int i = 0; i < n; i++) {
//            arr[i] = n - i;
//        }
//    }
//}
//
//// Функція для виведення таблиці
//void printResults(int n, const string& caseType, int bubbleComp, int bubbleSwap, int quickComp, int quickSwap, int shellComp, int shellSwap) {
//    cout << setw(10) << n << setw(15) << caseType
//        << setw(15) << bubbleComp << setw(10) << bubbleSwap
//        << setw(15) << quickComp << setw(10) << quickSwap
//        << setw(15) << shellComp << setw(10) << shellSwap << endl;
//}
//
//int main() {
//    SetConsoleOutputCP(1251);
//    SetConsoleCP(1251);
//
//    vector<int> arr;
//    int n[] = { 1000, 10000, 100000 }; // Масив розмірностей
//
//    cout << setw(10) << "N" << setw(15) << "Випадок" << setw(15) << "Bubble Comp" << setw(10) << "Bubble Swap"
//        << setw(15) << "Quick Comp" << setw(10) << "Quick Swap"
//        << setw(15) << "Shell Comp" << setw(10) << "Shell Swap" << endl;
//
//    for (int i = 0; i < 3; i++) { // Перебір для трьох розмірностей
//        for (int type = 1; type <= 3; type++) {
//            arr.resize(n[i]);
//            fillArray(arr, type);
//
//            // Bubble Sort
//            vector<int> arr1 = arr;
//            int bubbleComp, bubbleSwap;
//            bubbleSort(arr1, bubbleComp, bubbleSwap);
//
//            // Quick Sort
//            vector<int> arr2 = arr;
//            int quickComp = 0, quickSwap = 0;
//            quickSort(arr2, 0, n[i] - 1, quickComp, quickSwap);
//
//            // Shell Sort
//            vector<int> arr3 = arr;
//            int shellComp, shellSwap;
//            shellSort(arr3, shellComp, shellSwap);
//
//            // Виведення результатів
//            string caseType = (type == 1) ? "Найкращий" : (type == 2) ? "Середній" : "Найгірший";
//            printResults(n[i], caseType, bubbleComp, bubbleSwap, quickComp, quickSwap, shellComp, shellSwap);
//        }
//    }
//
//    return 0;
//}
