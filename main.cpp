#include <fstream>
#include <iostream>
#include "matrix.h"
#include <chrono>

using namespace std;
using namespace std::chrono;


template < class T >
std::ostream& operator << (std::ostream& os, const std::vector<T>& v)
{
//    os << "[";
    for (typename std::vector<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii)
    {
        os << *ii << endl;
    }
//    os << "]";
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
    p = stod( argv[2]);



    Matrix W(&input);
    Matrix D;
    D.buildDMatrix(W);

//    Empezamos a medir el tiempo de multiplicar
    timeType startMultiply = high_resolution_clock::now();

    W.multiplyMatrix(D);
//    Paramos el reloj
    timeType endMultiply= high_resolution_clock::now();
    duration<double> elapsedMultiply = duration_cast<duration<double>>(endMultiply - startMultiply);

    W.scalarMultiply(-p);
    Matrix I;
    I.buildIdentity(W.numberOfRows());

//    Empezamos a medir el tiempo de sumar
    timeType startAdd = high_resolution_clock::now();
    I.addMatrix(W);

//    Paramos el reloj
    timeType endAdd= high_resolution_clock::now();
    duration<double> elapsedAdd = duration_cast<duration<double>>(endAdd - startAdd);


//    I.logFullRep();
//    Empezamos a medir el tiempo de Gauss
    timeType startGauss = high_resolution_clock::now();
    I.gaussianEliminate();
//    Paramos el reloj
    timeType endGauss= high_resolution_clock::now();
    duration<double> elapsedGauss = duration_cast<duration<double>>(endGauss - startGauss);
//    I.logFullRep();


    vector<double> b(I.numberOfRows(),1);

//    Empezamos a medir el tiempo de resolver el sistema
    timeType startResolve = high_resolution_clock::now();

    vector<double> solution = I.resolveTheProlem(b);

//    Paramos el reloj
    timeType endResolve= high_resolution_clock::now();
    duration<double> elapsedResolve = duration_cast<duration<double>>(endResolve - startResolve);


    cerr << elapsedMultiply.count() << ';' <<elapsedAdd.count() << ';' << elapsedGauss.count() << ';' << elapsedResolve.count() << endl;
//
//
    cout << p << endl;
    cout <<  normalize(solution);
//
//
//


    return 0;

}