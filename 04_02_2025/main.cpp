#include <iostream>
#include <fstream>
#include <iomanip>


using namespace std;

const int MAX = 10;
const int NUM_DIRECCIONES = 8;
const int NUM_COORDENADAS = 2;

const int COORDENADAS[NUM_DIRECCIONES][NUM_COORDENADAS] = {-1,-1,-1,0, -1,1, 0,1,1,1,1,0,1,-1,0,-1};

typedef struct {
	int dimension;
	int matriz[MAX][MAX];
} tMatriz;


ostream& operator<<(ostream& out, const tMatriz& m);
bool cargarMatriz(ifstream& archivo, tMatriz& m);
istream& operator>>(istream& archivo, tMatriz& m);
void intercambiaDiagonales(tMatriz& m);
bool esPuntoSumidero(const tMatriz& m, int x, int y);
void muestraPuntosSumidero(const tMatriz& m);
bool esCreciente(const tMatriz& m, int x, int y, int incri, int incrj);
bool posicionValida(const tMatriz& m, int x, int y);


const tMatriz MAT_PRUEBA = { 3, {{27,18,13}, {17,5,30}, {18,19,16} } };

int main() {
	tMatriz m = MAT_PRUEBA;
	ifstream archivo;

	if (!cargarMatriz(archivo, m))
		cout << "El archivo no se puede abrir" << "\n";
	// 1.- carga la matriz m. Si falla manda un mensaje de error.
	//     En caso de que la carga haya sido correcta:
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


ostream& operator<<(ostream& out, const tMatriz& m) {
	for (int i = 0; i < m.dimension; i++) {
		for (int j = 0; j < m.dimension; j++) {
			out << setw(4) << m.matriz[i][j] << ' ';
		}
		out << endl;
	}
	return out;
}

istream& operator>>(istream& archivo, tMatriz& m)
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

void intercambiaDiagonales(tMatriz& m)
{
	int aux;

	for (int i = 0; i < m.dimension; i++)
	{
		aux = m.matriz[i][m.dimension - i - 1];
		m.matriz[i][m.dimension - i - 1] = m.matriz[i][i];
		m.matriz[i][i] = aux;
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

void muestraPuntosSumidero(const tMatriz& m)
{
	for (int i = 0; i < m.dimension; i++)
	{
		for (int j = 0; j < m.dimension; j++)
		{
			if (esPuntoSumidero(m, i, j))
			{
				cout << "(" << i << "," << j << "): " << m.matriz[i][j] << "\n";
			}
		}
	}
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
		if (m.matriz[xAct][yAct] > m.matriz[xSig][ySig])
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

bool posicionValida(const tMatriz& m, int x, int y)
{
	return (x >= 0 && x < m.dimension) && (y >= 0 && y < m.dimension);
}

bool cargarMatriz(ifstream& archivo, tMatriz &m)
{
	archivo.open("matriz.txt");
	bool exito = false;

	if (archivo.is_open())
	{
		archivo >> m;
		exito = true;
	}

	return exito;
}



