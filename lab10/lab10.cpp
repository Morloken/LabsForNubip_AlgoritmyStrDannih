#include <iostream>
#include <vector>
#include <windows.h>
#include <climits>

using namespace std;

const int V = 8; // Кількість вершин у графі

// Функція для відновлення шляху між двома вершинами
vector<int> reconstructPath(vector<vector<int>>& next, int u, int v) {
    if (next[u][v] == -1) {
        return {}; // Повертаємо порожній шлях, якщо шляху немає
    }
    vector<int> path = { u + 1 }; // Додаємо початкову вершину до шляху
    while (u != v) {
        u = next[u][v];
        path.push_back(u + 1); // Додаємо вершину до шляху
    }
    return path;
}

// Алгоритм Флойда-Воршелла для знаходження найкоротших шляхів і відновлення шляху
void floydWarshallWithPathReconstruction(int graph[V][V]) {
    vector<vector<int>> dist(V, vector<int>(V, INT_MAX)); // Матриця відстаней
    vector<vector<int>> next(V, vector<int>(V, -1)); // Матриця для відновлення шляху

    // Ініціалізація матриць `dist` та `next`
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (graph[i][j] != 0) {
                dist[i][j] = graph[i][j];
                next[i][j] = j;
            }
        }
        dist[i][i] = 0;
        next[i][i] = i;
    }

    // Основний цикл алгоритму Флойда-Воршелла
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }

    // Запит у користувача для вибору вершин
    int src, dest;
    cout << "Введіть номер початкової вершини: ";
    cin >> src;
    cout << "Введіть номер кінцевої вершини: ";
    cin >> dest;
    src--; dest--; // Зміщення на -1 для коректного індексу

    // Виведення результатів
    if (dist[src][dest] == INT_MAX) {
        cout << "Шляху від вершини " << src + 1 << " до вершини " << dest + 1 << " не існує." << endl;
    }
    else {
        cout << "Найкоротший шлях від вершини " << src + 1 << " до вершини " << dest + 1 << " дорівнює " << dist[src][dest] << endl;

        vector<int> path = reconstructPath(next, src, dest);
        cout << "Шлях: ";
        for (int v : path) {
            cout << v << " ";
        }
        cout << endl;
    }
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "");

    int graph[V][V] = {
        {0, 13, 0, 0, 0, 0, 16, 14}, // Вершина 1
        {0, 0, 4, 0, 0, 0, 0, 0},    // Вершина 2
        {0, 0, 0, 13, 0, 0, 9, 0},   // Вершина 3
        {0, 0, 0, 0, 8, 0, 0, 0},    // Вершина 4
        {0, 0, 0, 0, 0, 5, 12, 0},   // Вершина 5
        {0, 0, 0, 0, 0, 0, 13, 0},   // Вершина 6
        {0, 0, 0, 0, 0, 0, 0, 0},    // Вершина 7
        {0, 0, 0, 0, 0, 0, 0, 0}     // Вершина 8
    };

    floydWarshallWithPathReconstruction(graph);

    return 0;
}
