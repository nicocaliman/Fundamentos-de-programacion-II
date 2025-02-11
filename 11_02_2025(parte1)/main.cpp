#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "matrices.h"
#include "operadores.h"

using namespace std;

bool cargarMatriz(ifstream& archivo, tMatriz& m); 
void muestraPuntosSumidero(const tMatriz& m);
bool esPuntoSumidero(const tMatriz& m, int x, int y);
bool esCreciente(const tMatriz& m, int x, int y, int incri, int incrj);
void intercambiaDiagonales(tMatriz& m);

int main()
{
	tMatriz m;
	ifstream archivo;

	inicia(m, MAX);

	if (!cargarMatriz(archivo, m))
	{
		cout << "error al cargar la matriz" << endl;
	}

	else
	{

		cout << m;
		// 2.- muestra los puntos sumidero de m
		cout << "Los sumideros de la matriz son: " << endl;
		muestraPuntosSumidero(m);
		// 3.- intercambia las diagonales de m
		intercambiaDiagonales(m);
		cout << "La matriz con las diagonales principales intercambiadas es:" << endl;
		cout << m;
	}
	return 0;
}

bool cargarMatriz(ifstream& archivo, tMatriz& m)
{
	string nombreMatriz = "";
	bool ok = false;

	cout << "Introduce la matriz a cargar: ";
	cin >> nombreMatriz;

	archivo.open(nombreMatriz);

	if (archivo.is_open())
	{
		archivo >> m;

		ok = true;
	}

	return ok;
}

void muestraPuntosSumidero(const tMatriz& m)
{
	for (int i = 0; i < getDimension(m); i++)
	{
		for (int j = 0; j < getDimension(m); j++)
		{
			if (esPuntoSumidero(m, i, j))
			{
				cout << "(" << i << "," << j << "): " << getElem(m, i, j) << "\n";
			}
		}
	}
}

bool esPuntoSumidero(const tMatriz& m, int x, int y)
{
	bool esSumidero = true;
	int i = 0;

	while (i < NUM_DIRECCIONES && esSumidero)
	{
		if (!esCreciente(m, x, y, COORDENADAS[i][0], COORDENADAS[i][1]))
		{
			esSumidero = false;
		}

		++i;
	}


	return esSumidero;
}


bool esCreciente(const tMatriz& m, int x, int y, int incri, int incrj)
{
	int xSig = x + incri;
	int ySig = y + incrj;

	int xAct = x;
	int yAct = y;

	bool esCreciente = true;

	while (posicionValida(m, xSig, ySig) && esCreciente)
	{
		if (getElem(m, xAct, yAct) > getElem(m, xSig, ySig))
		{
			esCreciente = false;
		}

		else
		{
			xAct = xSig;
			yAct = ySig;

			xSig += incri;
			ySig += incrj;
		}
	}

	return esCreciente;
}

void intercambiaDiagonales(tMatriz& m)
{
	int aux;

	for (int i = 0; i < getDimension(m); i++)
	{
		aux = getElem(m, i, getDimension(m)-i-1);
		setElem(m, i, getDimension(m)-i-1, getElem(m, i,i));
		setElem(m, i, i, aux);
	}
}