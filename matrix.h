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
    explicit Matrix(ifstream* input);

    Matrix() {}

    void multiplyMatrix(Matrix a);
    void logContents();
    void buildFullRep();
    void logFullRep();
    void addMatrix(Matrix a);
    void scalarMultiply(int x);

    void gaussianEliminate();

    vector<double> ResolveTheProlem (vector<double> sol);
private:

    int totalLinks;
    int totalPages;

    vector<vector<double>> fullRep;

    vector<map<int, double>> fastRep;

    vector<map<int, double>> pivotalRep = {};

    vector<double> * getRowNumber(int i);

    vector<double> getColumnNumber(int i);

    double doVectorMultiplication(vector<double> *row, vector<double> *col);

    void setElement(vector<map<int,double>>* matrix,int i ,int j ,double a);

    void updateRowForGauss(int j, int i);

    void swapFastAndPivotal();

    int diagonalElement(int i);

    int rowWithTheHighestCoefficientInColumn(int i);

    double getElement(int update, int row);

    void pivotRows(int i, int column);
};




#endif //PAGERANK_MATRIX_H
