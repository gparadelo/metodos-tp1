//
// Created by mike on 28/03/18.
//

#include "matrix.h"

Matrix::Matrix(ifstream* input):totalLinks(5), totalPages(0) {

    if(!input->good()){
        cout << "The input file isn't good";
        assert(false);
    }

    *(input) >> totalPages >> totalLinks;

    int saliente, entrante;
    for (int i = 0; i < totalLinks; ++i) {
            *(input) >> saliente;
            *(input) >> entrante;
            vector<int> newLink = {entrante, saliente, 1};
            sparseRep.push_back(newLink);
    }
}

void Matrix::logContents() {
    for (int i = 0; i < totalLinks; ++i) {
        cout << '(' << sparseRep[i][0] << "," << sparseRep[i][1] << ") " << "con valor: " << sparseRep[i][2] << endl;
    }
}

void Matrix::buildFullRep() {
    vector<vector<int>> matriz(totalPages, vector<int>(totalPages, 0));
    fullRep = matriz;

    for (int k = 0; k < totalLinks; ++k) {
        vector<int> elem = sparseRep[k];
        fullRep[elem[0] -1 ][elem[1] -1 ] = elem[2];
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

        while (j >= 0 && sparseRep[j][0] > key[0])
        {
            sparseRep[j+1] = sparseRep[j];
            --j;
        }
        sparseRep[j+1] = key;
    }


    for (int i = 1; i < totalLinks; ++i) {
        key = sparseRep[i];
        j = i - 1;

        while (j >= 0 && sparseRep[j][1] > key[1] && sparseRep[j][0] >= key[0])
        {
            sparseRep[j+1] = sparseRep[j];
            --j;
        }
        sparseRep[j+1] = key;

    }

}