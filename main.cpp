#include <fstream>
#include <iostream>
#include "matrix.h"

using namespace std;

int main(int argc, char *argv[]){

    ifstream input(argv[1]);
    ifstream b("../tests/b.txt");
    int p (int argv[2]);

    Matrix W(&input);
    Matrix B(&b);

//    W.multiplyMatrix(B);
    W.logFullRep();
    W.gaussianEliminate();
    W.logFullRep();
//
    vector<double> sol({4,2,3});
    vector<double> res = W.resolveTheProlem(sol);

    cout << "Solucion: [" ;

    for (int i = 0; i < W.getTotalPages(); ++i)
    {
        cout << res[i] << ", ";
    }

    cout << "]";

//
//    B.logFullRep();
//
//    W.addMatrix(W);
//    W.logFullRep();
//
//    W.multiplyMatrix(B);
//    W.logFullRep();
//
//    int x = 3;
//    W.scalarMultiply(x);
//    W.logFullRep();
//
//    W.gaussianEliminate();
//    W.logFullRep();
//
//
//    vector<double> res = W.resolveTheProlem(sol);
//    cout << "Solucion: [" ;
//
//    for (int i = 0; i < W.getTotalPages(); ++i)
//    {
//        cout << res[i] << ", ";
//    }
//
//    cout << "]";

    return 0;

}