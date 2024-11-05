#include <iostream>
#include <string>
#include <windows.h>
#include <cctype> // Для функцій isdigit і isalpha
#include <regex>  // Для регулярних виразів

using namespace std;

struct Train {
    string number;
    string destination;
    string departureTime;
    Train* left;   // Нащадок (ліворуч)
    Train* right;  // Нащадок (праворуч)

    Train(string num, string dest, string time) : number(num), destination(dest),
       departureTime(time), left(nullptr), right(nullptr) {}
};

class TrainTree {//=====================================================================================          Class Train START
private:
    Train* root;//вказівник на кореневий елемент дерева.
    //У початковий момент він дорівнює nullptr, тобто дерево порожнє

    void insert(Train*& node, string num, string dest, string time) {
        if (node == nullptr) {
            //створення нового вузла
            node = new Train(num, dest, time);
        }
        else if (num < node->number) {//Якщо номер потяга num менший за номер 
            //в поточному вузлі (node->number), функція викликається рекурсивно для піддерева лівого 
            insert(node->left, num, dest, time);
        }
        else {
            insert(node->right, num, dest, time);
        }
    }

    void display(Train* node) {
        if (node != nullptr) {
            display(node->left);
            cout << "Номер потяга: " << node->number << ", Станція призначення: " <<
                node->destination << ", Час відправлення: " << node->departureTime << endl;
            display(node->right);
        }
    }
    /*
    Виводить інформацію про всі потяги в дереві, використовуючи симетричний обхід (in-order traversal):
    Рекурсивно обробляється ліве піддерево.
    Виводиться інформація про поточний вузол.
    Рекурсивно обробляється праве піддерево.
    Таким чином, потяги виводяться у порядку зростання їхніх номерів
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
    Виконує пошук потяга за номером. Працює рекурсивно:
        Якщо node == nullptr, значить потяг не знайдено.
        Якщо номер поточного вузла збігається з num, повертається цей вузол.
        Якщо num менше номера в поточному вузлі, рекурсія виконується для лівого піддерева.
    Інакше, викликається для правого піддерева.
    */

    void searchByDestination(Train* node, const string& dest) {
        if (node != nullptr) {
            searchByDestination(node->left, dest);//Рекурсивно обробляється ліве піддерево.
            if (node->destination == dest) {
                cout << "Номер потяга: " << node->number << ", Час відправлення: " << node->departureTime << endl;
            }
            searchByDestination(node->right, dest);//обробляється праве піддерево.
        }
    }

    void searchByTime(Train* node, const string& time) {
        if (node != nullptr) {
            searchByTime(node->left, time);
            if (node->departureTime == time) {
                cout << "Номер потяга: " << node->number << ", Станція призначення: " << node->destination << ", Час відправлення: " << node->departureTime << endl;
            }
            searchByTime(node->right, time);
        }
    }

public:
    TrainTree() : root(nullptr) {}// ініціалізація рут елемента з значенням 0ля, показуючи що на початку дерево - пусте

    void insert(string num, string dest, string time) {// додавання нового потяга
        insert(root, num, dest, time);
    }

    void display() {//вивести всю інформацію про потяги в дереві.
        display(root);
    }

    void findTrainByNumber(const string& num) {
        Train* train = searchByNumber(root, num);
        if (train) {
            cout << "Знайдений потяг: Номер потяга: " << train->number << ", Станція призначення: " << train->destination << ", Час відправлення: " << train->departureTime << endl;
        }
        else {
            cout << "Потяг з номером " << num << " не знайдено." << endl;
        }
    }

    void findTrainsByDestination(const string& dest) {
        cout << "Потяги до станції " << dest << ":" << endl;
        searchByDestination(root, dest);
    }

    void findTrainsByTime(const string& time) {
        cout << "Потяги, які відправляються о " << time << ":" << endl;
        searchByTime(root, time);
    }
};//=====================================================================================          Class Train END

// Функція для перевірки правильності введення станції призначення
bool isValidDestination(const string& destination) {
    // Перевірка, що станція складається з одного слова та містить лише англійські букви та цифри
    return regex_match(destination, regex("^[A-Za-z0-9]+$"));
}

// Функція для перевірки правильності введення часу
bool isValidTime(const string& time) {
    for (char c : time) {
        if (!isdigit(c) && c != ':' && c != ' ') {
            return false;
        }
    }
    return true;
}

// для перевірки правильності введення номера потяга
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
    int n;//Кільк. потягів

    cout << "Введіть кількість потягів: ";
    cin >> n;

    cout << "\n----Запис інформації про потяги----\n";
    for (int i = 0; i < n; i++) {
        string number, destination, departureTime;

        // Перевірка введення номера потяга
        do {
            cout << "Введіть номер потяга (тільки цифри): ";
            cin >> number;
            if (!isValidTrainNumber(number)) {
                cout << "Помилка: номер потяга може містити лише цифри.\n";
            }
        } while (!isValidTrainNumber(number));

        // Перевірка введення станції призначення
        do {
            cout << "Введіть станцію призначення (одне слово, лише англійські букви та цифри): ";
            cin >> destination;
            if (!isValidDestination(destination)) {
                cout << "Помилка: станція призначення має бути одним словом, яке містить лише англійські букви та цифри.\n";
            }
        } while (!isValidDestination(destination));

        // Перевірка введення часу
        do {
            cout << "Введіть час відправлення (тільки цифри та символи ':'): ";
            cin >> departureTime;
            if (!isValidTime(departureTime)) {
                cout << "Помилка: час має містити лише цифри та символи ':'.\n";
            }
        } while (!isValidTime(departureTime));

        tree.insert(number, destination, departureTime);
        cout << "\n----Наступний потяг----\n";
    }

    cout << "\n----Всі потяги----\n";
    tree.display();

    int choice;//вибір опції в меню
    do {
        cout << "\n----Меню----\n";
        cout << "1. Запитати станцію для виведення потягів.\n";
        cout << "2. Запитати номер потяга.\n";
        cout << "3. Запитати час для виведення потягів.\n";
        cout << "4. Вийти з програми.\n";
        cout << "Виберіть дію (1-4): ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string searchDestination;
            cout << "\nВведіть станцію призначення для пошуку потягів: ";
            cin >> searchDestination;
            tree.findTrainsByDestination(searchDestination);
            break;
        }
        case 2: {
            string searchNumber;
            cout << "\nВведіть номер потяга для пошуку: ";
            cin >> searchNumber;
            tree.findTrainByNumber(searchNumber);
            break;
        }
        case 3: {
            string searchTime;
            cout << "\nВведіть час для пошуку потягів: ";
            cin >> searchTime;
            tree.findTrainsByTime(searchTime);
            break;
        }
        case 4:
            cout << "Вихід з програми." << endl;
            break;
        default:
            cout << "Неправильний вибір. Спробуйте ще раз." << endl;
        }
    } while (choice != 4);

    return 0;
}
