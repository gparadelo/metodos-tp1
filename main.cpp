#include <fstream>
#include <iostream>
#include "matrix.h"

using namespace std;


template < class T >
std::ostream& operator << (std::ostream& os, const std::vector<T>& v)
{
    os << "[";
    for (typename std::vector<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii)
    {
        os << " " << *ii;
    }
    os << "]";
    return os;
}


int main(int argc, char *argv[]) {

    ifstream input(argv[1]);
    double p;
    p = stod( argv[2]);

    cout << p << endl;


    Matrix W(&input);
    Matrix D;
    D.buildDMatrix(W);

    W.logFullRep();
    W.multiplyMatrix(D);

    W.logFullRep();
    W.scalarMultiply(-p);
    W.logFullRep();

    Matrix I;
    I.buildIdentity(W.numberOfRows());

    I.addMatrix(W);

    I.logFullRep();

    I.gaussianEliminate();
    cout << "The matrix is:" << endl;
    I.logFullRep();

    vector<double> b(I.numberOfRows(),1);

    cout << "We want to find solutions for:" << endl;
    cout << b;

    vector<double> solution = I.resolveTheProlem(b);
    cout << "The solution is" << solution;





    return 0;

}