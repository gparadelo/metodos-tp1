#include <fstream>
#include <iostream>
#include "matrix.h"

int main(int argc, char *argv[]){

	ifstream input(argv[1]);

	matriz_rala mat;

	input >> mat.cant_pags;
	input >> mat.cant_links;

	int saliente;
	int entrante;

	for (int i = 0; i < mat.cant_links; i++)
	{
		input >> saliente;
		input >> entrante;
		mat.valores.push_back( make_tuple(entrante - 1, saliente - 1, (double)1) );
	}


/*
	//Test de valores
	for (int i = 0; i < mat.cant_links; i++)
	{
		cout << get<0>(mat.valores[i]) << " " << get<1>(mat.valores[i]) << " "  << get<2>(mat.valores[i]);
		cout << endl;
	}
*/


/*	//No funciona
	vector<vector<double>> matriz = mat.construirMatriz();

	for (int i = 0; i < matriz.size(); i++)
	{	
		for (int j = 0; i < matriz[i].size(); j++)
		{
			cout << matriz[i][j] << " ";
		}
		cout << endl;
	}
*/
	return 0;
}
