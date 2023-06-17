#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max(); // �������������

// ��������� ��� ������������� ����� �����
struct Edge {
    int destination;
    int weight;
};

// ������� ��� ������ ����������� ���� � ������� ��������� ��������
void Dijkstra(vector<vector<Edge>>& graph, int source, vector<int>& distances) {
    int n = graph.size();
    distances.resize(n, INF); // �������������� ���������� �� ���� ������ ��� �������������
    distances[source] = 0; // ���������� �� ��������� ������� ����� 0

    // ������� ������������ ������� (min-����), � ������� ����� ������� ���� (����������, �������)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push(make_pair(0, source)); // ��������� ��������� ������� � �������

    while (!pq.empty()) {
        int u = pq.top().second; // ��������� ������� � ���������� �����������
        pq.pop();

        // ������� �������� �������
        for (const Edge& edge : graph[u]) {
            int v = edge.destination;
            int weight = edge.weight;

            // ���� ������ ����� �������� ���� �� ������� v
            if (distances[u] != INF && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight; // ��������� ���������� �� ������� v
                pq.push(make_pair(distances[v], v)); // ��������� ������� v � �������
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    ifstream fin("input.txt");
    int n, m, source; // ���������� ������, �����, ��������� �������
    cout << "������� ���������� ������, ����� � ��������� �������: ";
    fin >> n >> m >> source;
    cout << n << " " << m << " " << source << endl;

    vector<vector<Edge>> graph(n); // ���� � ���� ������ ���������

    // ���� ����� �����
    cout << "������� ����� ����� � �������: ���������_������� ��������_������� ���\n";
    for (int i = 0; i < m; ++i) {
        int u, v, weight;
        fin >> u >> v >> weight;
        cout << u << " " << v << " " << weight << endl;
        graph[u].push_back({ v, weight });
        graph[v].push_back({ u, weight });
    }

    vector<int> distances; // ���������� �� ������ �� ��������� �������

    Dijkstra(graph, source, distances);

    // ����� ���������� ���������� �� ���� ������
    cout << "���������� ���������� �� ���� ������:\n";
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
