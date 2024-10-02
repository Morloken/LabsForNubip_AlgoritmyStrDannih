//1)           10. ����������� � ������� �� ����� ����� � 10 ���������� ����� ��  -140 �� 140, �� ���������� ����� ����� � �������� ������, �� ����� 30. 


// #include <iostream>
// #include <ctime>
// #include <cstdlib>

// using namespace std;

// int main() {
//     // --------------------------------------
//     srand(static_cast<unsigned int>(time(nullptr)));
//   /*
//   ������� static_cast, ������� �� ����� ����� �� ��, �� � ������� ���� ���������� ����. �� �������� �������� ������� �� ������� ����������� ����
//   */
//     // --------------------------------------
//     const int size = 10;
//     int array[size];
//     int greater_than_30[size]; // >30
//     int count = 0; // ��� ���������� ������� ��������, ������ �� 30

//     // ------------------------------------------
//     cout << "����� � ���������� �����:\n";
//     for (int i = 0; i < size; ++i) {
//         array[i] = rand() % 281 - 140; 
//         cout << array[i] << " ";
//         if (array[i] > 30) {
//             greater_than_30[count] = array[i]; // �������� ��������, ����� �� 30
//             count++; 
//         }
//     }
//     cout << "\n-------------------" << endl;
//     //------------------------------------------
//     cout << "\n����� � ��������, ������ �� 30:\n";
//     if (count == 0) {
//         cout << "���� ��������, ������ �� 30\n"; 
//     } else {
//         for (int i = 0; i < count; ++i) {
//             cout << greater_than_30[i] << " "; // ���� > 30
//         }
//         cout << endl;
//     }

//     return 0;
// }


//2)         10. ������ ��������� �������. ������ ���� �������� ��� �����, � ���� �� ������� ������� ����������� �䒺�� �����. 
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip> // ��� setw()
#include <vector>  // ��� std::vector

using namespace std;

int main() {

    srand(static_cast<unsigned int>(time(nullptr)));

    //------------------------------------------
    int size;
    cout << "������ ����� ��������� �������: ";
    cin >> size;

    //------------------------------------------
    // ������������ ������� ������ ���������� ������
    vector<vector<int>> matrix(size, vector<int>(size));

    cout << "\n�������:\n";
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = rand() % 201 - 100; // ��������� �������� � ������� [-100, 100]
            cout << setw(5) << matrix[i][j]; // ��������� � ������� ���� 5
        }
        cout << endl;
    }

    int sum = 0;
    cout << "\n�����, �� �� ������� ������� � ��'��� �����:\n";

    // �������� ������� ������� � ��������� ���� ����� � ��'������ ���������� �� �������
    for (int i = 0; i < size; ++i) {
        if (matrix[i][i] < 0) {
            int rowSum = 0;
            cout << "����� " << i + 1 << ": ";
            for (int j = 0; j < size; ++j) {
                rowSum += matrix[i][j];
                cout << setw(5) << matrix[i][j]; // ��������� � ������� ���� 5
            }
            sum += rowSum;
            cout << " | ���� �����: " << rowSum << endl;
        }
    }

    cout << "\n�������� ���� �������� �����, �� �� ������� ������� ��'��� �����: " << sum << endl;

    return 0;
}
