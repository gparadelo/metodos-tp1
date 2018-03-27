#include "matrix.h"

vector<vector<double>> matriz_rala::construirMatriz() {

vector<vector<double>> matriz(cant_pags, vector<double>(cant_pags));				//se crea una matriz de ceros

	for (int i = 0; i < cant_links; i++)
	{
		matriz[get<0>(valores[i])][get<1>(valores[i])] = get<2>(valores[i]);	//cada valor se asigna a su posicion correspondiente en la matriz
	}

	return matriz;
}