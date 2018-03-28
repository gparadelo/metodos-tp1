#include <fstream>
#include <iostream>
#include "matrix.h"

using namespace std;

int main(int argc, char *argv[]){

    ifstream input(argv[1]);
    int p (int argv[2]);

    Matrix W(&input);

    W.logContents();

    W.buildFullRep();
    W.logFullRep();

    return 0;

}