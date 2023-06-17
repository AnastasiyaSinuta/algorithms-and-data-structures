#include <iostream>
#include <fstream>
#include "Scheme.h"
#include "Operations.h"
using namespace std;

int main() {
    ifstream fin("input.txt");
    Scheme scheme1{ fin };
    fin.close();
    Operations mkt;
    mkt.contourMethod(scheme1.C_Matrix, scheme1.Z_Matrix, scheme1.E_Matrix);
    return 0;
}
