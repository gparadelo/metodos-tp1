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

    W.buildFullRep();
    W.logFullRep();
    W.addMatrix(W);

    W.buildFullRep();
    W.logFullRep();


    B.buildFullRep();
    B.logFullRep();

    W.multiplyMatrix(B);

    W.logFullRep();


    return 0;

}