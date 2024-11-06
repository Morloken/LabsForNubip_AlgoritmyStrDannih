#include <iostream>
#include <vector>
#include <windows.h>
#include <climits>

using namespace std;

const int V = 8; // ʳ������ ������ � �����

// ������� ��� ���������� ����� �� ����� ���������
vector<int> reconstructPath(vector<vector<int>>& next, int u, int v) {
    if (next[u][v] == -1) {
        return {}; // ��������� ������� ����, ���� ����� ����
    }
    vector<int> path = { u + 1 }; // ������ ��������� ������� �� �����
    while (u != v) {
        u = next[u][v];
        path.push_back(u + 1); // ������ ������� �� �����
    }
    return path;
}

// �������� ������-�������� ��� ����������� ����������� ������ � ���������� �����
void floydWarshallWithPathReconstruction(int graph[V][V]) {
    vector<vector<int>> dist(V, vector<int>(V, INT_MAX)); // ������� ��������
    vector<vector<int>> next(V, vector<int>(V, -1)); // ������� ��� ���������� �����

    // ����������� ������� `dist` �� `next`
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

    // �������� ���� ��������� ������-��������
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

    // ����� � ����������� ��� ������ ������
    int src, dest;
    cout << "������ ����� ��������� �������: ";
    cin >> src;
    cout << "������ ����� ������ �������: ";
    cin >> dest;
    src--; dest--; // ������� �� -1 ��� ���������� �������

    // ��������� ����������
    if (dist[src][dest] == INT_MAX) {
        cout << "����� �� ������� " << src + 1 << " �� ������� " << dest + 1 << " �� ����." << endl;
    }
    else {
        cout << "����������� ���� �� ������� " << src + 1 << " �� ������� " << dest + 1 << " ������� " << dist[src][dest] << endl;

        vector<int> path = reconstructPath(next, src, dest);
        cout << "����: ";
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
        {0, 13, 0, 0, 0, 0, 16, 14}, // ������� 1
        {0, 0, 4, 0, 0, 0, 0, 0},    // ������� 2
        {0, 0, 0, 13, 0, 0, 9, 0},   // ������� 3
        {0, 0, 0, 0, 8, 0, 0, 0},    // ������� 4
        {0, 0, 0, 0, 0, 5, 12, 0},   // ������� 5
        {0, 0, 0, 0, 0, 0, 13, 0},   // ������� 6
        {0, 0, 0, 0, 0, 0, 0, 0},    // ������� 7
        {0, 0, 0, 0, 0, 0, 0, 0}     // ������� 8
    };

    floydWarshallWithPathReconstruction(graph);

    return 0;
}
