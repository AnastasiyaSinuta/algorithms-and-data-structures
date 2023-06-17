#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max(); // Бесконечность

// Структура для представления ребра графа
struct Edge {
    int destination;
    int weight;
};

// Функция для поиска кратчайшего пути с помощью алгоритма Дейкстры
void Dijkstra(vector<vector<Edge>>& graph, int source, vector<int>& distances) {
    int n = graph.size();
    distances.resize(n, INF); // Инициализируем расстояния до всех вершин как бесконечность
    distances[source] = 0; // Расстояние до начальной вершины равно 0

    // Создаем приоритетную очередь (min-кучу), в которой будем хранить пары (расстояние, вершина)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push(make_pair(0, source)); // Добавляем начальную вершину в очередь

    while (!pq.empty()) {
        int u = pq.top().second; // Извлекаем вершину с наименьшим расстоянием
        pq.pop();

        // Обходим соседние вершины
        for (const Edge& edge : graph[u]) {
            int v = edge.destination;
            int weight = edge.weight;

            // Если найден более короткий путь до вершины v
            if (distances[u] != INF && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight; // Обновляем расстояние до вершины v
                pq.push(make_pair(distances[v], v)); // Добавляем вершину v в очередь
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    ifstream fin("input.txt");
    int n, m, source; // Количество вершин, ребер, начальная вершина
    cout << "Введите количество вершин, ребер и начальную вершину: ";
    fin >> n >> m >> source;
    cout << n << " " << m << " " << source << endl;

    vector<vector<Edge>> graph(n); // Граф в виде списка смежности

    // Ввод ребер графа
    cout << "Введите ребра графа в формате: начальная_вершина конечная_вершина вес\n";
    for (int i = 0; i < m; ++i) {
        int u, v, weight;
        fin >> u >> v >> weight;
        cout << u << " " << v << " " << weight << endl;
        graph[u].push_back({ v, weight });
        graph[v].push_back({ u, weight });
    }

    vector<int> distances; // Расстояния до вершин от начальной вершины

    Dijkstra(graph, source, distances);

    // Вывод кратчайших расстояний до всех вершин
    cout << "Кратчайшие расстояния до всех вершин:\n";
    for (int i = 0; i < n; ++i) {
        if (distances[i] == INF) {
            cout << "INF ";
        }
        else {
            cout << distances[i] << " ";
        }
    }

    return 0;
}
