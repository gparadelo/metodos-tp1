#include <vector>
#include <tuple>

using namespace std;

class matriz_rala {
public:
	int cant_pags;
	int cant_links;
	vector<tuple <int, int, double> > valores;		// (fila, columna, valor)

	vector<vector<double> > construirMatriz();
	//convierte la lista de tuplas en una matriz propiamente dicha. Sirve para realizar operaciones.

};