//
// Created by mike on 28/03/18.
//

#include "matrix.h"

Matrix::Matrix(ifstream *input) {

    if (!input->good()) {
        cout << "The input file isn't good";
        assert(false);
    }

    *(input) >> totalPages >> totalLinks;


//    Inicializamos la nueva representacion de vector de filas que serán map
    for (int j = 0; j < totalPages; ++j) {
        map<int, double> newMap;
        fastRep.push_back(newMap);
    }


    int saliente, entrante;
    for (int i = 0; i < totalLinks; ++i) {
        *(input) >> saliente;
        *(input) >> entrante;
        pair<int, double> elem(saliente - 1, 1);
        fastRep[entrante - 1].insert(elem);
    }


}

void Matrix::logContents() {
    cout << "Fast Rep contents:" << endl;
    for (int k = 0; k < totalPages; ++k) {
        for (auto j: fastRep[k]) {
            cout << '(' << k << "," << j.first << ") " << "con valor: " << j.second << endl;
        }
    }
}

void Matrix::buildFullRep() {
    vector<vector<double>> matriz((unsigned long)totalPages, vector<double>(totalPages, 0));
    fullRep = matriz;

    for (int i = 0; i < totalPages; ++i) {
        auto it = fastRep[i].begin();

        while(it != fastRep[i].end()){
            fullRep[i][it->first] = it->second;
            it++;
        }
    }

}

void Matrix::logFullRep() {
    buildFullRep();
    cout << "Logging full rep:" << endl;
    for (int i = 0; i < totalPages; ++i) {
        for (int j = 0; j < totalPages; ++j) {
            cout << fullRep[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl << endl;
}


//Modifica la matriz original
void Matrix::addMatrix(Matrix a) {
    assert(totalPages == a.totalPages);

//    Para cada fila O(n)
    for (int i = 0; i < totalPages; ++i) {

//        Para cada columna de la fila
//        O(elementos de la fila)
        map<int, double>::iterator aIt = a.fastRep[i].begin();
        while (aIt != a.fastRep[i].end()) {

//            Si está también en la matriz original
//            O(log (elementos de la fila))
            map<int, double>::iterator it = fastRep[i].find(aIt->first);

//            O(log(elementos de la fila))
            if (fastRep[i].find(aIt->first) != fastRep[i].end()) {
                it->second += aIt->second;
            } else {
                fastRep[i].insert(*(aIt));
            }
            aIt++;
        }
    }
}

void Matrix::multiplyMatrix(Matrix a) {
    assert(totalPages == a.totalPages);

    buildFullRep();
    a.buildFullRep();
    for (int i = 0; i < totalPages; ++i) {
       vector<double> * row = getRowNumber(i);
        for (int j = 0; j < totalPages; ++j) {
            vector<double> col = a.getColumnNumber(j);

//            Since a column isn't easily accessible from vector of rows representation, we build it and then pass the reference
//            to the function
            double elem = doVectorMultiplication(row,&col);
            setElement(&pivotalRep, i,j,elem);
        }
    }

    swapFastAndPivotal();

    buildFullRep();
}

vector<double> * Matrix::getRowNumber(int i) {
    return &fullRep[i];
}

vector<double>  Matrix::getColumnNumber(int j) {
    vector<double> res(totalPages,0);

    for (int i = 0; i < totalPages; ++i) {
        res[i] = fullRep[i][j];
    }

    return res;
}

double Matrix::doVectorMultiplication(vector<double> *row, vector<double> *col) {
    assert(row->size() == col->size());

    double acc = 0 ;
    for (int i = 0; i < row->size(); ++i) {
        acc += (*row)[i] * (*col)[i];
    }

    return acc;
}

void Matrix::setElement(vector<map<int,double >>* matrix, int i , int j, double a) {
    while(matrix->size()  < i + 1){
        map<int, double> newMap;
        matrix->push_back(newMap);
    }
    pair<int, double> elem(j, a);
    (*matrix)[i].insert(elem);
}

void Matrix::swapFastAndPivotal() {
    fastRep.swap(pivotalRep);
}

void Matrix::gaussianEliminate() {
    cout << "Doing gauss" << endl;
    for (int i = 0; i < fastRep.size(); ++i) {
//        Para cada fila
        int a = diagonalElement(i);
        if(a == 0) {
            pivotRows(i, rowWithTheHighestCoefficientInColumn(i));
        }
        int b = diagonalElement(i);
        if(b == 0 ){
            continue;
        }
        for (int j = i + 1; j < fastRep.size(); ++j) {
//            Para cada fila que le sigue
            updateRowForGauss(j,i);
            logFullRep();

        }
    }

}

void Matrix::updateRowForGauss(int rowToUpdate, int mainRow) {
        map<int, double>::iterator it = fastRep[rowToUpdate].begin();
        while(it != fastRep[rowToUpdate].end()){
            int aToZeroOut = getElement(rowToUpdate, it->first);
            it->second -= aToZeroOut / diagonalElement(mainRow) * (getElement(mainRow,it->first));
            it++;
        }
}



int Matrix::rowWithTheHighestCoefficientInColumn(int i) {
    int maxRow = i;
    int max = diagonalElement(i);
    for (int j = i; j < totalPages; ++j) {
        map<int,double> * currentRow= &fastRep[j];
        map<int,double>::iterator it = currentRow->find(i);
        if(it != currentRow->end()){
            if (it->second > max){
                maxRow = j;
                max = it->second;
            }
        }
    }
    return maxRow;
}

double Matrix::getElement(int row, int col) {
    if(fastRep[row].find(col) != fastRep[row].end()){
        return fastRep[row].find(col)->second;
    }
    return 0;
}

int Matrix::diagonalElement(int i) {
    return getElement(i,i);
}

void Matrix::pivotRows(int i, int j) {
    swap(fastRep[i],fastRep[j]);
}

void Matrix::scalarMultiply(int x) {
    for (int i = 0; i < totalPages; ++i) {
        map<int,double>::iterator it = fastRep[i].begin();

        while (it != fastRep[i].end()) {
            it->second *= x;
            it++;
        }
    }

}










