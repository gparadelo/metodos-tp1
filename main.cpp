#include <fstream>
#include <iostream>
#include "matrix.h"
#include <chrono>

using namespace std;
using namespace std::chrono;


template < class T >
std::ostream& operator << (std::ostream& os, const std::vector<T>& v)
{
    for (typename std::vector<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii)
    {
        os << *ii << endl;
    }
    return os;
}

vector<double> normalize(vector<double> &v);
vector<double> normalize(vector<double> &v){
    double acc = 0;
    for (int i = 0; i < v.size(); ++i) {
        acc += v[i];
    }
    for (int j = 0; j < v.size(); ++j) {
        v[j] = v[j]/acc;
    }
    return v;
}



typedef high_resolution_clock::time_point timeType;
int main(int argc, char *argv[]) {

    ifstream input(argv[1]);

    double p;
    p = stod(argv[2]);

    ofstream resultsFile;
    ofstream timeFile;
    resultsFile.open("../experimentacion/results/results.out");
    timeFile.open("../experimentacion/results/time",std::ios_base::app);


    Matrix W(&input);
    int totalLinks = W.getTotalLinks();
    Matrix D;
    D.buildDMatrix(W);


//    MULTIPLICAMOS MATRICES
    timeType startMultiply = high_resolution_clock::now();
    W.multiplyMatrix(D);
    timeType endMultiply= high_resolution_clock::now();
    duration<double> elapsedMultiply = duration_cast<duration<double>>(endMultiply - startMultiply);



//    MUTLIPLICAMOS POR UN ESCALAR
    W.scalarMultiply(-p);



//    FORMAMOS LA IDENTIDAD
    Matrix I;
    I.buildIdentity(W.numberOfRows());


//    SUMAMOS MATRICES
    timeType startAdd = high_resolution_clock::now();
    I.addMatrix(W);
    timeType endAdd= high_resolution_clock::now();
    duration<double> elapsedAdd = duration_cast<duration<double>>(endAdd - startAdd);



//    ELIMINACION GAUSSIANA
    timeType startGauss = high_resolution_clock::now();
    I.gaussianEliminate();
    timeType endGauss= high_resolution_clock::now();
    duration<double> elapsedGauss = duration_cast<duration<double>>(endGauss - startGauss);





//    BACKWARDS SUBSTITUTION
    timeType startResolve = high_resolution_clock::now();
    vector<double> solution = I.solve();
    timeType endResolve= high_resolution_clock::now();
    duration<double> elapsedResolve = duration_cast<duration<double>>(endResolve - startResolve);




//    LOG EVERYTHING
    cerr << elapsedMultiply.count() << ';' <<elapsedAdd.count() << ';' << elapsedGauss.count() << ';' << elapsedResolve.count() << endl;


    timeFile << I.numberOfRows() << ';' << totalLinks << ';' << p << ';' << elapsedMultiply.count() << ';' <<elapsedAdd.count() << ';' << elapsedGauss.count() << ';' << elapsedResolve.count() << endl;

    cout << p << endl;
    cout <<  normalize(solution);

    resultsFile << p << endl;
    resultsFile <<  normalize(solution);

    resultsFile.close();
    timeFile.close();


    return 0;

}