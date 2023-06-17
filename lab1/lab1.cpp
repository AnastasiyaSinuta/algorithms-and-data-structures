#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    ifstream fin("input.txt");
    vector<vector<int>> matrix;

    string line;
    while (getline(fin, line)) {
        vector<int> row;
        istringstream iss(line);
        int value;
        while (iss >> value) {
            row.push_back(value);
        }
        matrix.push_back(row);
    }

    // Выводим матрицу
    cout << "Matrix:" << endl;
    for (const auto& row : matrix) {
        for (const auto& value : row) {
            cout << value << " ";
        }
        cout << endl;
    }
    cout << endl;

    size_t numRows = matrix.size();
    size_t numCols = matrix[0].size();

    // Проверка наличия решений
    if (numCols != numRows + 1) {
        cout << "The system has no solutions." << endl;
        return 0;
    }

    int n = numRows;
    vector<vector<double>> A(n, vector<double>(n));
    vector<double> b(n);
    vector<double> x(n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            A[i][j] = matrix[i][j];
        }
        b[i] = matrix[i][n];
    }

    // Приведение матрицы коэффициентов к ступенчатому виду
    for (int k = 0; k < n; k++)
    {
        for (int i = k + 1; i < n; i++)
        {
            if (A[k][k] == 0)
            {
                swap(A[k], A[k + 1]);
                swap(b[k], b[k + 1]);
                continue;
            }
            double coeff = A[i][k] / A[k][k];
            for (int j = k; j < n; j++)
            {
                A[i][j] -= coeff * A[k][j];
            }
            b[i] -= coeff * b[k];
        }
    }

    // Проверка единственного решения
    for (int i = 0; i < n; i++)
    {
        if (A[i][i] == 0)
        {
            if (b[i] != 0)
            {
                cout << "The system has no solutions." << endl;
                return 0;
            }
            cout << "The system has an infinite number of solutions." << endl;
            return 0;
        }
    }

    // Нахождение решения системы
    for (int i = n - 1; i >= 0; i--)
    {
        double sum = 0;
        for (int j = i + 1; j < n; j++)
        {
            sum += A[i][j] * x[j];
        }
        x[i] = (b[i] - sum) / A[i][i];
    }

    // Вывод решения
    cout << "System solution:";
    for (int i = 0; i < n; i++)
    {
        cout << endl << "x" << i + 1 << " = " << x[i];
    }
    cout << endl;
    return 0;
}
