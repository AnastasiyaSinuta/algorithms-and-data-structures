#ifndef __SCHEME__
#define __SCHEME__
#include <fstream>
#include <vector>
using namespace std;

class Scheme
{
public:
    vector<vector<double>> C_Matrix;
    vector<vector<double>> Z_Matrix;
    vector<vector<double>> E_Matrix;
    Scheme(ifstream& fin);
private:
    int branches;
    int contours;
    vector<vector<double>> create_C_Matrix(ifstream& fin, int branches, int contours);
    vector<vector<double>> create_Z_Matrix(ifstream& fin, int branches, int contours);
    vector<vector<double>> create_E_Matrix(ifstream& fin, int branches, int contours);
};
#endif