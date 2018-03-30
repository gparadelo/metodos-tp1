//
// Created by mike on 28/03/18.
//

#ifndef PAGERANK_MATRIX_H
#define PAGERANK_MATRIX_H

#include <fstream>
#include <iostream>
#include <vector>
#include <cassert>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <string>

using namespace std;


class Matrix {

public:
    Matrix(ifstream* input);

    void logContents();
    void buildFullRep();
    void logFullRep();
    void sortSparseRep();

    void addMatrix(Matrix a);


private:

    int totalLinks;
    int totalPages;

    vector<vector<int>> sparseRep;
    vector<vector<int>> fullRep;

    vector<map<int, double>> fastRep;


};




#endif //PAGERANK_MATRIX_H
