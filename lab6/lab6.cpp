//�������� �������� �� ��� �++, ��� ����������� ���������, ��
//������� �������� �������� �����, �������� �������.

//10. ����������� � ������� �� ����� ����� � 10 ���������� ����� ��
//-140 �� 140, �� ���������� ����� ����� � �������� ������, �� ����� 30

#include <iostream>
#include <cstdlib>  //  rand() �� srand()
#include <ctime>    //  time()
#include <windows.h>
#include <locale> // ��� ������ � ��������

using namespace std;

int main() {
    setlocale(LC_ALL, ""); // ������������ ����� �� ����� ��������� ���������� (��� �������� ��������)

    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    srand(time(0)); 

    // �������� ���'��� ��� ������ � 10 ��������
    int* arr = new int[10];

    // �������� ����� �� -140 �� 140 � ���������� ������
    cout << "����� � 10 ���������� ����� �� -140 �� 140:\n";
    for (int i = 0; i < 10; ++i) {
        arr[i] = rand() % 281 - 140; 
        cout << arr[i] << " ";
    }
    cout << endl;

    // ������� ��������, �� ����� 30
    int count = 0;
    for (int i = 0; i < 10; ++i) {
        if (arr[i] > 30) {
            ++count;
        }
    }

    //  �������� ���'��� ��� ������ ������
    int* filteredArr = new int[count];

    // ����� ����� ���������, �� ����� 30
    int j = 0;
    for (int i = 0; i < 10; ++i) {
        if (arr[i] > 30) {
            filteredArr[j++] = arr[i];
        }
    }

    // ���� ������ ������
    cout << "����� ��������, �� ����� 30:\n";
    for (int i = 0; i < count; ++i) {
        cout << filteredArr[i] << " ";
    }
    cout << endl;

    // �������� �������� ���'��
    delete[] arr;
    delete[] filteredArr;

    return 0;
}
