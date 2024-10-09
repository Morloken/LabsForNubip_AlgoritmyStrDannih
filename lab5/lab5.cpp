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
 * ������� ���������� ���������� (Bubble Sort).---------------------------------------------------
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
 * ������� �������� ���������� (QuickSort) �� ������� �����.--------------------------------------------
 * ����������� ����� ��������� ��� ���������� ������.
 * ��� ����� �������� (����� �� 10 ��������)
 * ����������� ������� ���������� ��� ��������� �������������.
 * ������ ���������: O(n log n) � ���������� �������.
 */
void quickSort(vector<int>& arr, int low, int high) {
    while (low < high) {
        // ���� ������� �������� � ������� ����� �� ����, ������������� insertion sort
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

        int pivot = arr[low];  // ���� �������� ��������
        int left = low;
        int right = high;

        while (left < right) {
            // ����� ��������, ������� �� pivot � ������� ����
            while (arr[right] >= pivot && left < right) {
                comparisons++;
                right--;
            }
            if (left != right) {
                arr[left] = arr[right];
                exchanges++;
                left++;
            }
            // ����� ��������, ������� �� pivot � ����� ����
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
        arr[left] = pivot;  // ������� �������� �������� �� ��������� �������
        exchanges++;

        // ������� ������ ������� ����������, � ������ ����������
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
 * ������� ���������� ����� (Shell Sort).------------------------------------------------
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
void fillBestCase(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = i;
    }
}

/**
 * ������� ��� ���������� ������ � ��������� �������.
 * �������� ����� � ������������� ���������� � ���������� �������
 * (�� n-1 �� 0).
 */
void fillWorstCase(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = arr.size() - i;
    }
}

/**
 * ������� ��� ���������� ������ ����������� ����������.
 * ������ �������� ����� �� maxValue ��� ������� �������� ������.
 */
void fillRandomCase(vector<int>& arr, int maxValue) {
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

/**
 * ������� ������� ��������.
 * ����������� ��� ������ ���������� �� ������� ����� ������
 * �� ���������� �������, � ����� �������� ���������� � �������.
 */
int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    srand(time(0));
    const int sizes[] = { 1000, 10000, 20000 };  // ������ ������ ��� ����������

    for (int n : sizes) {
        vector<int> arr(n);

        // ������� ��� Bubble Sort
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

        // ������� ��� QuickSort
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

        // ������� ��� Shell Sort
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
    }

    return 0;
}

// ����������� ������� �������� ���������� (QuickSort) � ������������� ������� ��� ����� ��������
// ������������ ������ ��� ������� ��������, � �������� � ��� �������

// ������� ��� ���������� ������ � ���������� ������� (��� ������������)

// ������� ��� ���������� ������ � ��������� ������� (������������ � ���������� �������)

// ������� ��� ���������� ������ ����������� ����������