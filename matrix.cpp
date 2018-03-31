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
        vector<int> newLink = {entrante, saliente, 1};
        sparseRep.push_back(newLink);


        pair<int, double> elem(saliente - 1, 1);
        fastRep[entrante - 1].insert(elem);
    }


}

void Matrix::logContents() {
//    for (int i = 0; i < totalLinks; ++i) {
//        cout << '(' << sparseRep[i][0] - 1 << "," << sparseRep[i][1] - 1 << ") " << "con valor: " << sparseRep[i][2]
//             << endl;
//    }

    cout << "Fast Rep contents:" << endl;
    for (int k = 0; k < totalPages; ++k) {
        for (auto j: fastRep[k]) {
            cout << '(' << k << "," << j.first << ") " << "con valor: " << j.second << endl;
        }
    }
}

void Matrix::buildFullRep() {
    vector<vector<int>> matriz(totalPages, vector<int>(totalPages, 0));
    fullRep = matriz;

//    for (int k = 0; k < totalLinks; ++k) {
//        vector<int> elem = sparseRep[k];
//        fullRep[elem[0] - 1][elem[1] - 1] = elem[2];
//    }

//
    for (int i = 0; i < totalPages; ++i) {
        map<int, double>::iterator it = fastRep[i].begin();

        while(it != fastRep[i].end()){
            fullRep[i][it->first] = it->second;
            it++;
        }
        cout << endl;
    }

}

void Matrix::logFullRep() {
    cout << "Logging full rep:" << endl;
    for (int i = 0; i < totalPages; ++i) {
        for (int j = 0; j < totalPages; ++j) {
            cout << fullRep[i][j] << ' ';
        }
        cout << endl;
    }
}

void Matrix::sortSparseRep() {
//Bucket sort primero por filas, luego por columnas.
//Sirve para realizar operaciones mas eficientes.
//Insertion Sort para que sea lineal si ya esta ordenado.

    int i, j;
    vector<int> key;

    for (int i = 1; i < totalLinks; ++i) {
        key = sparseRep[i];
        j = i - 1;

        while (j >= 0 && sparseRep[j][0] > key[0]) {
            sparseRep[j + 1] = sparseRep[j];
            --j;
        }
        sparseRep[j + 1] = key;
    }


    for (int i = 1; i < totalLinks; ++i) {
        key = sparseRep[i];
        j = i - 1;

        while (j >= 0 && sparseRep[j][1] > key[1] && sparseRep[j][0] >= key[0]) {
            sparseRep[j + 1] = sparseRep[j];
            --j;
        }
        sparseRep[j + 1] = key;

    }

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
    for (int i = 0; i < totalPages; ++i) {
       vector<int> * row = getRowNumber(i);
        for (int j = 0; j < totalPages; ++j) {
            vector<int> col = a.getColumnNumber(j);

//            Since a column isnt easily accessible from vector of rows representation, we build it and then pass the reference
//            to the function
            int elem = doVectorMultiplication(row,&col);
            setElement(i,j,elem);
        }
    }

    swapFastAndPivotal();

    buildFullRep();
}

vector<int> * Matrix::getRowNumber(int i) {
    return &fullRep[i];
}

vector<int>  Matrix::getColumnNumber(int j) {
    vector<int> res(totalPages,0);

    for (int i = 0; i < totalPages; ++i) {
        res[i] = fullRep[i][j];
    }

    return res;
}

int Matrix::doVectorMultiplication(vector<int> *row, vector<int> *col) {
    assert(row->size() == col->size());

    int acc = 0 ;
    for (int i = 0; i < row->size(); ++i) {
        acc += (*row)[i] * (*col)[i];
    }

    return acc;
}

void Matrix::setElement(int i , int j, double a) {
    while(pivotalRep.size()  < i + 1){
        map<int, double> newMap;
        pivotalRep.push_back(newMap);
    }
    pair<int, double> elem(j, a);
    pivotalRep[i].insert(elem);
}

void Matrix::swapFastAndPivotal() {
    fastRep.swap(pivotalRep);
}







