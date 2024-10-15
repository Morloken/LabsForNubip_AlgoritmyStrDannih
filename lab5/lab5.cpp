#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>   // ��� rand()
#include <ctime>     // ��� time()
#include <iomanip>   // ��� setw � ������������ �������
#include <windows.h>
using namespace std;

// �������� ���� ��� ��������� ������� �������� �� �����
int comparisons = 0;
int exchanges = 0;

/**
 * ����� ��������� �������� �� ����� �� ����.
 * ��������������� ����� �������� ������� ��������� ����������
 * ��� ��������� ������ ����������.
 */
void resetCounters() {
    comparisons = 0;
    exchanges = 0;
}

/**
 * ������� ���������� ���������� (Bubble Sort).---------------------------------------------------   Bubble Sort
 * ������ �������� ������������� �����, ���� ���������
 * ����� �����, ������� ����� �������� � ������ ��,
 * ���� ���� �� � ����������� �������.
 * ������ ���������: O(n^2) � ��������� �������.
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
 * ������� �������� ���������� (QuickSort) �� ������� �����.--------------------------------------------  QuickSort
 * ����������� ����� ��������� ��� ���������� ������.
 * ��� ����� �������� (����� �� 10 ��������)
 * ����������� ������� ���������� ��� ��������� �������������.
 * ������ ���������: O(n log n) � ���������� �������.
 */

// ������� ��� ��������� ������
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];  // �������� ������� ������� �� �������
    int i = low - 1;  // ������ ��� ��������, ������ �� pivot

    for (int j = low; j <= high - 1; j++) {
        comparisons++;  // ˳���� ���������
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);  // ���� ��������
            exchanges++;  // ˳���� �����
        }
    }

    swap(arr[i + 1], arr[high]);  // ������������ pivot �� ��������� �������
    exchanges++;  // ˳���� �����
    return i + 1;  // ��������� ������ �������� ��������
}

// ��������� ������� �������� �����
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);  // �������� ������� �������� ��������

        // ��������� ������� ��� ��������
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}





/**
 * ������� ���������� ����� (Shell Sort).------------------------------------------------    Shell Sort
 * ������ �������� ���������� �����, ���� �������� ��
 * �������� �� ���� �������� �� ����� ��������
 * (gap), �� ����������� � ������ ���������.
 * ������ ���������: O(n^(3/2)) � ���������� �������.
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
 * ������� ��� ���������� ������ � ���������� �������.
 * �������� ����� � ������������� ���������� (�� 0 �� n-1).
 */
void fillBestCase(vector<int>& arr) {//========================================       BEST
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = i;
    }
}

/**
 * ������� ��� ���������� ������ � ��������� �������.
 * �������� ����� � ������������� ���������� � ���������� �������
 * (�� n-1 �� 0).
 */



void fillWorstCase(vector<int>& arr) {//==========================================        WORST
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = arr.size() - i - 1;  // �� n-1 �� 0
    }
}


//void fillWorstCase(vector<int>& arr) {
//    for (int i = arr.size() - 1; i >= 0; i--) {
//        arr[i] = i;  // �� n-1 �� 0
//    }
//}

/**
 * ������� ��� ���������� ������ ����������� ����������.
 * ������ �������� ����� �� maxValue ��� ������� �������� ������.
 */
void fillRandomCase(vector<int>& arr, int maxValue) {//===============================     RANDOM
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = rand() % maxValue;
    }
}

/**
 * ������� ��� ��������� ��������� ������� � ������������.
 * �������� ��������� ������� ��� ������� ������ ����������
 * � ��������� ������� ��������.
 */
void printTableHeader(const string& methodName, int n) {
    cout << "\n\n===============================" << endl;
    cout << "   " << methodName << " Results (N = " << n << ")" << endl;
    cout << "===============================" << endl;
    cout << "|   Case   | Comparisons | Exchanges |" << endl;
    cout << "--------------------------------------" << endl;
    cout.flush();  // ������� ���� ���������
}

/**
 * ������� ��� ��������� ����� � ������������.
 * �������� ������� �������� �� ����� ��� ������� �������
 * (���������, �������, ��������).
 */
void printTableRow(const string& caseName) {
    cout << "| " << setw(8) << caseName << " | "
        << setw(11) << comparisons << " | "
        << setw(9) << exchanges << " |" << endl;
    cout.flush();  // ������� ���� ���������
}

void printingAllArrays(const vector<int>& arr, const string& arrayName) {
    cout << "\n\n\n" << arrayName << ": --[ \n";
    for (int i = 0; i < arr.size(); i++) {
        cout << setw(4) << arr[i] << " ";
    }
    cout << "\n]--" << endl;
}






/**
 * ������� ������� ��������.
 * ����������� ��� ������ ���������� �� ������� ����� ������
 * �� ���������� �������, � ����� �������� ���������� � �������.
 */
int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    srand(time(0));


    const int sizes[] = { 10, 100, 200 };  // ������ ������ ��� ����������
    //const int sizes[] = { 1000, 10000, 100000 };

    for (int n : sizes) {//��������� �����������, �� �� ������������� ������, ��� ���������� ���������. ������� ���� ��� ��� ����������

        vector<int> arr(n);

        // ���������� ������ ����������� ����������
        fillRandomCase(arr, n);

        cout << "\n\n===============================\n";
        cout << "   Arrays Before Sorting (N = " << n << ")\n";
        cout << "===============================\n";

        // ��������� ������ ����� �����������
        printingAllArrays(arr, "Random Array");

        cout << "--------------------------------------" << endl;
        Sleep(50); // ��������
    }

    

    for (int n : sizes) {//����������� �������� ������ �� �������� �� �������
        vector<int> arr(n);

        //Sorting
        cout << "\n\n===============================================\n";
        cout << "\t\t\t\t\tSORTING\n";
        cout << "===============================================\n";

        // -------------------------------------------------������� ��� Bubble Sort
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
        Sleep(50);  // ��������

        // ---------------------------------------------------------������� ��� QuickSort
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
        Sleep(50);  // ��������

        // --------------------------------------------------------������� ��� Shell Sort
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
        Sleep(50);  // ��������



        // ������� ������ ���� �������
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

