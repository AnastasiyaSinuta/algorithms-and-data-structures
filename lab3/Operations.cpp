#include <iostream>
#include <vector>
#include <fstream>
#include "Operations.h"
using namespace std;

// Функция для вывода подробного решения в файл detailed_solution.txt
void Operations::print(ofstream& fout, string name, vector<vector<double>> matrix) {
    fout << endl << name << " = " << endl;
    for (const auto& row : matrix) {
        for (const auto& element : row) {
            fout << element << " ";
        }
        fout << endl;
    }
};

// Функция для перемножения матриц
vector<vector<double>> Operations::multiplyMatrices(const vector<vector<double>>& matrix1, const vector<vector<double>>& matrix2) {
    int rows1 = static_cast<int>(matrix1.size());
    int cols1 = static_cast<int>(matrix1[0].size());
    int rows2 = static_cast<int>(matrix2.size());
    int cols2 = static_cast<int>(matrix2[0].size());

    // Проверка совместимости размерностей матриц
    if (cols1 != rows2) {
        cout << "Ошибка: Несовместимые размерности матриц!" << endl;
        return vector<vector<double>>();
    }

    vector<vector<double>> result(rows1, vector<double>(cols2, 0));

    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols2; ++j) {
            for (int k = 0; k < cols1; ++k) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return result;
};

// Функция для транспонирования матрицы
vector<vector<double>> Operations::transposeMatrix(const vector<vector<double>>& matrix) {
    int rows = static_cast<int>(matrix.size());
    int cols = static_cast<int>(matrix[0].size());

    vector<vector<double>> transposed(cols, vector<double>(rows, 0));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            transposed[j][i] = matrix[i][j];
        }
    }

    return transposed;
};

// Функция для решения системы линейных уравнений методом Гаусса
vector<vector<double>> Operations::solveLinearSystem(const vector<vector<double>>& matrix, const vector<vector<double>>& columnVector) {
    int n = static_cast<int>(matrix.size());
    int m = static_cast<int>(matrix[0].size());

    // Проверка совместимости размерностей матриц
    if (n != m || n != columnVector.size()) {
        cout << "Ошибка: Некорректные размерности матриц!" << endl;
        return vector<vector<double>>();
    }

    vector<vector<double>> augmentedMatrix(n, vector<double>(m + 1, 0));

    // Создание расширенной матрицы системы
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            augmentedMatrix[i][j] = matrix[i][j];
        }
        augmentedMatrix[i][m] = columnVector[i][0];
    }

    // Прямой ход метода Гаусса
    for (int i = 0; i < n - 1; ++i) {
        if (augmentedMatrix[i][i] == 0) {
            // Поиск ненулевого элемента в текущем столбце для выполнения перестановки строк
            int rowToSwap = -1;
            for (int k = i + 1; k < n; ++k) {
                if (augmentedMatrix[k][i] != 0) {
                    rowToSwap = k;
                    break;
                }
            }

            if (rowToSwap == -1) {
                cout << "Ошибка: Система не имеет единственного решения!" << endl;
                return vector<vector<double>>();
            }

            // Перестановка строк
            swap(augmentedMatrix[i], augmentedMatrix[rowToSwap]);
        }

        for (int j = i + 1; j < n; ++j) {
            double ratio = augmentedMatrix[j][i] / augmentedMatrix[i][i];
            for (int k = i; k < m + 1; ++k) {
                augmentedMatrix[j][k] -= ratio * augmentedMatrix[i][k];
            }
        }
    }

    // Обратный ход метода Гаусса
    vector<vector<double>> solution(n, vector<double>(1, 0));
    for (int i = n - 1; i >= 0; --i) {
        double sum = 0;
        for (int j = i + 1; j < n; ++j) {
            sum += augmentedMatrix[i][j] * solution[j][0];
        }
        solution[i][0] = (augmentedMatrix[i][m] - sum) / augmentedMatrix[i][i];
    }

    return solution;
};

// Метод контурных токов
void Operations::contourMethod(vector<vector<double>> C_Matrix, vector<vector<double>>Z_Matrix, vector<vector<double>>E_Matrix) {
    ofstream fout("detailed_solution.txt");
    fout << "(C * Z * C^T) * I = C * E" << endl;

    vector<vector<double>> C_Z = multiplyMatrices(C_Matrix, Z_Matrix);
    print(fout, "C * Z", C_Z);

    vector<vector<double>> C_T = transposeMatrix(C_Matrix);
    print(fout, "C^T", C_T);

    vector<vector<double>> C_Z_C_T = multiplyMatrices(C_Z, C_T);
    print(fout, "C * Z * C^T", C_Z_C_T);

    vector<vector<double>> C_E = multiplyMatrices(C_Matrix, E_Matrix);
    print(fout, "C * E", C_E);

    vector<vector<double>> II = solveLinearSystem(C_Z_C_T, C_E);
    print(fout, "II", II);

    vector<vector<double>> I = multiplyMatrices(C_T, II);
    int i = 0;
    cout << "ANSWER I = " << endl;
    for (const auto& row : I) {
        for (const auto& element : row) {
            i++;
            cout << "I" << i << " = " << element << " ";
        }
        cout << endl;
    }
    print(fout, "ANSWER I", I);
};
