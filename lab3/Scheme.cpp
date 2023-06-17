#include <iostream>
#include <vector>
#include <fstream>
#include "Scheme.h"
using namespace std;

Scheme::Scheme(ifstream& fin)
{
    fin >> branches;
    cout << "number of branches: " << branches << endl;
    fin >> contours;
    cout << "number of contours: " << contours << endl << endl;

    C_Matrix = create_C_Matrix(fin, branches, contours);
    Z_Matrix = create_Z_Matrix(fin, branches, contours);
    E_Matrix = create_E_Matrix(fin, branches, contours);
};

vector<vector<double>> Scheme::create_C_Matrix(ifstream& fin, int branches, int contours)
{
    // матрица контуров
    cout << "Contour Matrix (C): " << endl;
    vector<vector<double>> C_Matrix(contours, vector<double>(branches));
    for (auto& row : C_Matrix) {
        for (int i = 0; i < branches; i++) {
            fin >> row[i];
            cout << row[i] << " ";
        }
        cout << endl;
    }
    cout << endl;
    return C_Matrix;
};

vector<vector<double>> Scheme::create_Z_Matrix(ifstream& fin, int branches, int contours)
{
    // вектор сопротивлений
    cout << "Resistance Vector (Z): " << endl;
    vector<double> resistanceVector(branches);
    vector<vector<double>> Z_Matrix(branches, vector<double>(branches));
    for (int i = 0; i < branches; i++) {
        fin >> resistanceVector[i];
        Z_Matrix[i][i] = resistanceVector[i];
        cout << Z_Matrix[i][i] << " ";
    }
    cout << endl << endl;
    return Z_Matrix;
};

vector<vector<double>> Scheme::create_E_Matrix(ifstream& fin, int branches, int contours)
{
    // вектор ЭДС
    cout << "EMF Vector (E): " << endl;
    vector<double> EMFVector(branches);
    vector<vector<double>> E_Matrix(branches, vector<double>(1));
    for (int i = 0; i < branches; i++) {
        fin >> EMFVector[i];
        E_Matrix[i][0] = EMFVector[i];
        cout << E_Matrix[i][0] << " ";
    }
    cout << endl << endl;
    return E_Matrix;
};
