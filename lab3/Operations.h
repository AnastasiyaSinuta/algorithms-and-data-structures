#ifndef __OPERATIONS__
#define __OPERATIONS__
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Operations
{
public:
    void contourMethod(vector<vector<double>> C_Matrix, vector<vector<double>>Z_Matrix, vector<vector<double>>E_Matrix);
private:
    void print(ofstream& fout, string name, vector<vector<double>> matrix);
    vector<vector<double>> multiplyMatrices(const vector<vector<double>>& matrix1, const vector<vector<double>>& matrix2);
    vector<vector<double>> transposeMatrix(const vector<vector<double>>& matrix);
    vector<vector<double>> solveLinearSystem(const vector<vector<double>>& matrix, const vector<vector<double>>& constantTerms);
};

#endif