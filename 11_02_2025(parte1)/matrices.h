#pragma once

#include <fstream>
#include <iomanip>

using namespace std;

const int MAX = 10;
const int  NUM_DIRECCIONES = 8;
const int NUM_COORDENADAS = 2;

const int COORDENADAS[NUM_DIRECCIONES][NUM_COORDENADAS] = { -1,-1,-1,0, -1,1, 0,1,1,1,1,0,1,-1,0,-1 };

typedef struct 
{
	int dimension;
	int matriz[MAX][MAX];
} tMatriz;

void inicia(tMatriz& m, int d);
bool posicionValida(const tMatriz& m, int i, int j);
int getDimension(const tMatriz& m);
int getElem(const tMatriz& m, int i, int j);
void setElem(tMatriz& m, int i, int j, int n);

