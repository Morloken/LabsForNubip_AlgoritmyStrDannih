#include <iostream>
#include <string>
#include <windows.h>
#include <cctype> // ��� ������� isdigit � isalpha
#include <regex>  // ��� ���������� ������

using namespace std;

struct Train {
    string number;
    string destination;
    string departureTime;
    Train* left;   // ������� (������)
    Train* right;  // ������� (��������)

    Train(string num, string dest, string time) : number(num), destination(dest),
       departureTime(time), left(nullptr), right(nullptr) {}
};

class TrainTree {//=====================================================================================          Class Train START
private:
    Train* root;//�������� �� ��������� ������� ������.
    //� ���������� ������ �� ������� nullptr, ����� ������ ������

    void insert(Train*& node, string num, string dest, string time) {
        if (node == nullptr) {
            //��������� ������ �����
            node = new Train(num, dest, time);
        }
        else if (num < node->number) {//���� ����� ������ num ������ �� ����� 
            //� ��������� ���� (node->number), ������� ����������� ���������� ��� �������� ����� 
            insert(node->left, num, dest, time);
        }
        else {
            insert(node->right, num, dest, time);
        }
    }

    void display(Train* node) {
        if (node != nullptr) {
            display(node->left);
            cout << "����� ������: " << node->number << ", ������� �����������: " <<
                node->destination << ", ��� �����������: " << node->departureTime << endl;
            display(node->right);
        }
    }
    /*
    �������� ���������� ��� �� ������ � �����, �������������� ����������� ����� (in-order traversal):
    ���������� ������������ ��� ��������.
    ���������� ���������� ��� �������� �����.
    ���������� ������������ ����� ��������.
    ����� �����, ������ ���������� � ������� ��������� ���� ������
    */


    Train* searchByNumber(Train* node, const string& num) {
        if (node == nullptr || node->number == num) {
            return node;
        }
        else if (num < node->number) {
            return searchByNumber(node->left, num);
        }
        else {
            return searchByNumber(node->right, num);
        }
    }
    /*
    ������ ����� ������ �� �������. ������ ����������:
        ���� node == nullptr, ������� ����� �� ��������.
        ���� ����� ��������� ����� �������� � num, ����������� ��� �����.
        ���� num ����� ������ � ��������� ����, ������� ���������� ��� ����� ��������.
    ������, ����������� ��� ������� ��������.
    */

    void searchByDestination(Train* node, const string& dest) {
        if (node != nullptr) {
            searchByDestination(node->left, dest);//���������� ������������ ��� ��������.
            if (node->destination == dest) {
                cout << "����� ������: " << node->number << ", ��� �����������: " << node->departureTime << endl;
            }
            searchByDestination(node->right, dest);//������������ ����� ��������.
        }
    }

    void searchByTime(Train* node, const string& time) {
        if (node != nullptr) {
            searchByTime(node->left, time);
            if (node->departureTime == time) {
                cout << "����� ������: " << node->number << ", ������� �����������: " << node->destination << ", ��� �����������: " << node->departureTime << endl;
            }
            searchByTime(node->right, time);
        }
    }

public:
    TrainTree() : root(nullptr) {}// ����������� ��� �������� � ��������� 0��, ��������� �� �� ������� ������ - �����

    void insert(string num, string dest, string time) {// ��������� ������ ������
        insert(root, num, dest, time);
    }

    void display() {//������� ��� ���������� ��� ������ � �����.
        display(root);
    }

    void findTrainByNumber(const string& num) {
        Train* train = searchByNumber(root, num);
        if (train) {
            cout << "��������� �����: ����� ������: " << train->number << ", ������� �����������: " << train->destination << ", ��� �����������: " << train->departureTime << endl;
        }
        else {
            cout << "����� � ������� " << num << " �� ��������." << endl;
        }
    }

    void findTrainsByDestination(const string& dest) {
        cout << "������ �� ������� " << dest << ":" << endl;
        searchByDestination(root, dest);
    }

    void findTrainsByTime(const string& time) {
        cout << "������, �� ������������� � " << time << ":" << endl;
        searchByTime(root, time);
    }
};//=====================================================================================          Class Train END

// ������� ��� �������� ����������� �������� ������� �����������
bool isValidDestination(const string& destination) {
    // ��������, �� ������� ���������� � ������ ����� �� ������ ���� �������� ����� �� �����
    return regex_match(destination, regex("^[A-Za-z0-9]+$"));
}

// ������� ��� �������� ����������� �������� ����
bool isValidTime(const string& time) {
    for (char c : time) {
        if (!isdigit(c) && c != ':' && c != ' ') {
            return false;
        }
    }
    return true;
}

// ��� �������� ����������� �������� ������ ������
bool isValidTrainNumber(const string& number) {
    for (char c : number) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

int main() {//======================================================                  MAIN
    setlocale(LC_ALL, "");

    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    TrainTree tree;
    int n;//ʳ���. ������

    cout << "������ ������� ������: ";
    cin >> n;

    cout << "\n----����� ���������� ��� ������----\n";
    for (int i = 0; i < n; i++) {
        string number, destination, departureTime;

        // �������� �������� ������ ������
        do {
            cout << "������ ����� ������ (����� �����): ";
            cin >> number;
            if (!isValidTrainNumber(number)) {
                cout << "�������: ����� ������ ���� ������ ���� �����.\n";
            }
        } while (!isValidTrainNumber(number));

        // �������� �������� ������� �����������
        do {
            cout << "������ ������� ����������� (���� �����, ���� �������� ����� �� �����): ";
            cin >> destination;
            if (!isValidDestination(destination)) {
                cout << "�������: ������� ����������� �� ���� ����� ������, ��� ������ ���� �������� ����� �� �����.\n";
            }
        } while (!isValidDestination(destination));

        // �������� �������� ����
        do {
            cout << "������ ��� ����������� (����� ����� �� ������� ':'): ";
            cin >> departureTime;
            if (!isValidTime(departureTime)) {
                cout << "�������: ��� �� ������ ���� ����� �� ������� ':'.\n";
            }
        } while (!isValidTime(departureTime));

        tree.insert(number, destination, departureTime);
        cout << "\n----��������� �����----\n";
    }

    cout << "\n----�� ������----\n";
    tree.display();

    int choice;//���� ����� � ����
    do {
        cout << "\n----����----\n";
        cout << "1. �������� ������� ��� ��������� ������.\n";
        cout << "2. �������� ����� ������.\n";
        cout << "3. �������� ��� ��� ��������� ������.\n";
        cout << "4. ����� � ��������.\n";
        cout << "������� �� (1-4): ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string searchDestination;
            cout << "\n������ ������� ����������� ��� ������ ������: ";
            cin >> searchDestination;
            tree.findTrainsByDestination(searchDestination);
            break;
        }
        case 2: {
            string searchNumber;
            cout << "\n������ ����� ������ ��� ������: ";
            cin >> searchNumber;
            tree.findTrainByNumber(searchNumber);
            break;
        }
        case 3: {
            string searchTime;
            cout << "\n������ ��� ��� ������ ������: ";
            cin >> searchTime;
            tree.findTrainsByTime(searchTime);
            break;
        }
        case 4:
            cout << "����� � ��������." << endl;
            break;
        default:
            cout << "������������ ����. ��������� �� ���." << endl;
        }
    } while (choice != 4);

    return 0;
}
