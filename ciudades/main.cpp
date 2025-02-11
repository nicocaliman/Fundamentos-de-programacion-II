#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const int MAX_FILAS = 50;	//maximo de filas
const int MAX_COLUMNAS = 50;	//maximo de columnas
const int NUM_DIRECCIONES = 8;
const int VECTOR_DIRECCION = 2;
const int MAXIMO_CIUDADES = 10;

const int DIRECCIONES[NUM_DIRECCIONES][VECTOR_DIRECCION] = { -1, -1, -1, 0, -1, 1, 0, 1, 1, 1, 1, 0,1, -1, 0, -1 };


typedef int tMatriz[MAX_FILAS][MAX_COLUMNAS];

typedef struct tCiudad
{
	int f;
	int c;

	tMatriz matriz;
};

typedef tCiudad tArray[MAXIMO_CIUDADES];

typedef struct tListaCiudades
{
	int numCiudades;
	tArray listaCiudades;
};

void cargarCiudad(ifstream& archivo, tCiudad& ciudad);
istream& operator>>(istream& in, tCiudad& ciudad);
void mostrarCiudad(const tCiudad& ciudad);
int edificiosVisibles(const tCiudad& c, int i, int j);
int edificiosVisiblesDir(const tCiudad& c, int i, int j, int incri, int incrj);
bool enRango(int i, int j, const tCiudad& c);
void cargarListaCiudades(ifstream& archivo, tListaCiudades& lc);
void mostrarListaCiudades(const tListaCiudades& lc);
double mediaVisibilidad(const tCiudad& ciudad);
int mejorCiudad(const tListaCiudades& lc);
bool operator<(double valor, const tCiudad& c2);

int main()
{
	ifstream archivo;
	tCiudad ciudad;

	cargarCiudad(archivo, ciudad);

	mostrarCiudad(ciudad);

	//pedir fila y columna al usuario
	int fila = 0;
	int columna = 0;

	bool error = false;

	while (!error)
	{
		cout << "Valor de x, entre 0 y 5: "; cin >> fila;
		cout << "Valor de y, entre 0 y 5: "; cin >> columna;

		if (!enRango(fila, columna, ciudad))
		{
			error = true;
		}

		else
		{
			cout << "Los edificios visibles desde (" << fila << "," << columna << ") = " << ciudad.matriz[fila][columna] << " son: " << edificiosVisibles(ciudad, fila, columna) << "\n";
		}
	}

	tListaCiudades lc;
	ifstream archivo1;

	cargarListaCiudades(archivo1, lc);

	mostrarListaCiudades(lc);

	for (int i = 0; i < lc.numCiudades; i++)
	{
		cout << "La visibilidad media de la CIUDAD " << i << " es " << mediaVisibilidad(lc.listaCiudades[i]) << "\n";
	}

	cout << "\n";

	cout << "La ciudad con mejor visiblidad media es la CIUDAD " << mejorCiudad(lc) << "\n";

	archivo.close();
	archivo1.close();

	return 0;
}

void cargarCiudad(ifstream& archivo, tCiudad& ciudad)
{
	archivo.open("ciudad.txt");

	if (archivo.is_open())
	{
		archivo >> ciudad;
	}
	else
	{
		cout << "El archivo ciudad.txt no existe" << "\n";
	}
}

void mostrarCiudad(const tCiudad& ciudad)
{
	for (int i = 0; i < ciudad.f; i++)
	{
		for (int j = 0; j < ciudad.c; j++)
		{
			cout << setw(5) << ciudad.matriz[i][j] << setw(5);
		}

		cout << "\n";
	}
}

int edificiosVisibles(const tCiudad& c, int i, int j)
{
	int edificiosVisibles = 0;	//contador

	for (int k = 0; k < NUM_DIRECCIONES; k++)
	{
		edificiosVisibles += edificiosVisiblesDir(c, i, j, DIRECCIONES[k][0], DIRECCIONES[k][1]);
	}

	return edificiosVisibles;
}

int edificiosVisiblesDir(const tCiudad& c, int i, int j, int incri, int incrj)
{
	int visibles = 0;

	int x = i + incri;
	int y = j + incrj;

	int altura = INT_MIN;

	while (enRango(x, y, c))
	{
		if (altura <= c.matriz[x][y])
		{
			altura = c.matriz[x][y];
			visibles++;
		}

		x += incri;
		y += incrj;
	}

	return visibles;
}

bool enRango(int i, int j, const tCiudad& c)
{
	return (i >= 0 && i < c.f) && (j >= 0 && j < c.c);
}

void cargarListaCiudades(ifstream& archivo, tListaCiudades& lc)
{
	archivo.open("ciudades.txt");

	if (archivo.is_open())
	{
		archivo >> lc.numCiudades;

		for (int i = 0; i < lc.numCiudades; i++)
		{
			archivo >> lc.listaCiudades[i];
		}
	}

	else
	{
		cout << "El archivo ciudades.txt no existe" << "\n";
	}
}

void mostrarListaCiudades(const tListaCiudades& lc)
{
	for (int i = 0; i < lc.numCiudades; i++)
	{
		cout << "CIUDAD NUMERO: " << i << "\n";
		mostrarCiudad(lc.listaCiudades[i]);
	}
}

double mediaVisibilidad(const tCiudad& ciudad)
{
	double numVisibles = 0;
	double numEdificios = 0;
	double media = 0;

	for (int i = 0; i < ciudad.f; i++)
	{
		for (int j = 0; j < ciudad.c; j++)
		{
			numVisibles += edificiosVisibles(ciudad, i,j);
			++numEdificios;
		}
	}

	media = numVisibles / numEdificios;

	return media;
}

int mejorCiudad(const tListaCiudades& lc)
{
	double mediaMejorVisble = mediaVisibilidad(lc.listaCiudades[0]);
	int mejorIndice = 0;

	for (int i = 1; i < lc.numCiudades; i++)
	{
		if (mediaMejorVisble < lc.listaCiudades[i])
		{
			mejorIndice = i;
			mediaMejorVisble = mediaVisibilidad(lc.listaCiudades[i]);
		}
	}

	return mejorIndice;
}

bool operator<(double valor, const tCiudad& c2) 
{
	return valor < mediaVisibilidad(c2);
}

// Sobrecarga del operador >>
istream& operator>>(istream& in, tCiudad& ciudad)
{
	in >> ciudad.f >> ciudad.c; // Leer el número de filas y columnas

	// Leer la matriz de la ciudad
	for (int i = 0; i < ciudad.f; i++) {
		for (int j = 0; j < ciudad.c; j++) {
			in >> ciudad.matriz[i][j];
		}
	}

	return in;
}
