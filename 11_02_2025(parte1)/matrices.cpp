#include "matrices.h"

void inicia(tMatriz& m, int d)
{
	m.dimension = d;
}

bool posicionValida(const tMatriz& m, int i, int j)
{
	return (i >= 0 && i < m.dimension) && (j >= 0 && j < m.dimension);
}

int getDimension(const tMatriz& m)
{
	return m.dimension;
}

int getElem(const tMatriz& m, int i, int j)
{
	return m.matriz[i][j];
}

void setElem(tMatriz& m, int i, int j, int n)
{
	m.matriz[i][j] = n;
}
