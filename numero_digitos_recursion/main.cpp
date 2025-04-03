#include <iostream>

using namespace std;

long long numero_digitos(int n);

int main()
{
    int n;

    cout << "Introduce un numero: ";
    cin >> n;

    cout << numero_digitos(n) << "\n";

    return 0;
}

long long numero_digitos(int n)
{
    int contador = 0;
    //caso base
    if (n < 10)
    {
        contador++;
    }

    else    //>=10
    {
        contador = 1 + numero_digitos(n/10);
    }    

    return contador;
}