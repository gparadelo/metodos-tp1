//
// Created by mike on 28/03/18.
//

#ifndef PAGERANK_MATRIX_H
#define PAGERANK_MATRIX_H

#include <fstream>
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

class Matrix {

public:
    Matrix(ifstream* input);

    void logContents();
    void buildFullRep();
    void logFullRep();

private:

    int totalLinks;
    int totalPages;

    vector<vector<int>> sparseRep;
    vector<vector<int>> fullRep;


};




#endif //PAGERANK_MATRIX_H
