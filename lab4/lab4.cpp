//10. ����� �� 0 �� 500, �� �� ������������ � � � ����� A, � � � B.
//��������� ������: �������, Գ������.
//����� ������ ����� ����� ������ �� 500 �������� �� ����������� ������� � ���������� �� 0 �� N-1. N=1000;
//��������� ������� �������� ��� �������� ����� ���������

#include <iostream>
#include <algorithm>

using namespace std;

// ������� ��� �������� ������
int binarySearch(int arr[], int size, int target, int& comparisons) {
    int low = 0;
    int high = size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        comparisons++;
        if (arr[mid] == target) {
            return mid;
        }
        comparisons++;
        if (arr[mid] < target) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return -1;  // ���� �� ��������
}

// ������� ��� ������ Գ�������
int fibonacciSearch(int arr[], int size, int target, int& comparisons) {
    // ����� ��� ����� Գ�������
    int fib2 = 0;  // (m-2)'� ����� Գ�������
    int fib1 = 1;  // (m-1)'� ����� Գ�������
    int fibM = fib2 + fib1;  // m'� ����� Գ�������

    // ��������� �������� ����� Գ������� ����� ��� ���� size
    while (fibM < size) {
        fib2 = fib1;
        fib1 = fibM;
        fibM = fib2 + fib1;
    }

    // ������� �� ������ ������� ������
    int offset = -1;//���������� ������� ������ ������ � �����.

    while (fibM > 1) {
        // ���������� �� ������ �������
        int i = min(offset + fib2, size - 1);/* ���� (offset + fib2) ����� (size - 1), �� ������������� (size - 1),
        ��� � (offset + fib2), ���� (offset + fib2) ����� (size - 1)
        */
        /*
        ���� ������������, ���� ����� Գ������� ����� 1. � ���� ���������� ������ i ��� ���������, ���� ����������� �� ����� �� offset + fib2 � ������� �������� ������ (size - 1). �� ������� ��� ��������� ������ �� ��� ������.
        */
        comparisons++;
        if (arr[i] < target) {// ���� ������� ������ arr[i] ����� target, �� offset ���������� �� �������� fib1
            fibM = fib1;
            fib1 = fib2;
            fib2 = fibM - fib1;
            offset = i;
        }
        else if (arr[i] > target) {// ���� ������� ������ arr[i] ����� target, �� offset ���������� �� �������� fib2
            fibM = fib2;
            fib1 = fib1 - fib2;
            fib2 = fibM - fib1;
        }
        else {
            return i;  // ��������
        }
    }

    // ���� ��������� ���� �������, ���������� ����
    if (fib1 && arr[offset + 1] == target) {
        comparisons++;
        return offset + 1;
    }

    return -1;  // ���� �� ��������
}

int main() {
    const int N = 20;// ʳ������ �������� � �������
    const int SEARCH_RANGE = 15;// ĳ������ ������
    int A[SEARCH_RANGE], B[SEARCH_RANGE];

    // ���������� ������ ����������� ������� (��� �������� ������ ������ ������)
    for (int i = 0; i < SEARCH_RANGE; ++i) {
        A[i] = rand() % N;
        cout << "\nA[" << i << "] = " << A[i];

    }
    cout << endl;

    for (int i = 0; i < SEARCH_RANGE; ++i) {
        B[i] = rand() % N;
        cout << "\nB[" << i << "] = " << B[i];

    }
    // B[i] = rand() % N;
   // ������� ������ ��� ������������ ������
    sort(A, A + SEARCH_RANGE);// ������� sort() ����������� �������� ���������� ���������� ��� ���������� ������ A
    sort(B, B + SEARCH_RANGE);//���������� ���������� ��� ������ B

    int binaryComparisons = 0;
    int fibonacciComparisons = 0;

    cout << "�����, �� �� ������� � ����� � ������:" << endl;

    for (int i = 0; i <= SEARCH_RANGE; ++i) {
        // ����� � ���� �������
        int binA = binarySearch(A, SEARCH_RANGE, i, binaryComparisons);//SEARCH_RANGE = 500
        int binB = binarySearch(B, SEARCH_RANGE, i, binaryComparisons);
        int fibA = fibonacciSearch(A, SEARCH_RANGE, i, fibonacciComparisons);
        int fibB = fibonacciSearch(B, SEARCH_RANGE, i, fibonacciComparisons);

        // ���� �� �������� � ������� � ������
        if (binA == -1 && binB == -1 && fibA == -1 && fibB == -1) {
            cout << i << "\t";
        }
    }
    // //���� ���� ������ a � �
    // for( )

    cout << "\n------------------" << endl;
    cout << "ʳ������ �������� (������� �����): " << binaryComparisons << endl;
    cout << "ʳ������ �������� (����� Գ�������): " << fibonacciComparisons << endl;

    return 0;
}