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
            vector<int> newLink = {saliente, entrante, 1};
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
