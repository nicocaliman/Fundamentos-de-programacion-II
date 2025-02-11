#include "operadores.h"

ostream& operator<<(ostream& out, const tMatriz& m)
{
	for (int i = 0; i < m.dimension; i++) {
		for (int j = 0; j < m.dimension; j++) {
			out << setw(4) << m.matriz[i][j] << ' ';
		}
		out << endl;
	}
	return out;
}

ifstream& operator>>(ifstream& archivo, tMatriz& m)
{
	archivo >> m.dimension;

	for (int i = 0; i < m.dimension; i++)
	{
		for (int j = 0; j < m.dimension; j++)
		{
			archivo >> m.matriz[i][j];
		}
	}

	return archivo;
}
