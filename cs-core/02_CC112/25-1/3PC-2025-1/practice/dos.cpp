#include <iostream>
using namespace std;

void crearMatriz(long long ***matriz, int filas, int columnas)
{
  *matriz = new long long *[filas];
  for (int i = 0; i < filas; i++)
  {
    (*matriz)[i] = new long long[columnas];
  }
}

void liberarMatriz(long long **matriz, int filas)
{
  for (int i = 0; i < filas; i++)
  {
    delete[] matriz[i];
  }
  delete[] matriz;
}

void copiarMatriz(long long **destino, long long **origen, int filas, int columnas)
{
  for (int i = 0; i < filas; i++)
  {
    for (int j = 0; j < columnas; j++)
    {
      destino[i][j] = origen[i][j];
    }
  }
}

void multiplicarMatrices(long long **A, long long **B, long long **resultado, int n)
{
  long long **temp;
  crearMatriz(&temp, n, n);

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      temp[i][j] = 0;
      for (int k = 0; k < n; k++)
      {
        temp[i][j] += A[i][k] * B[k][j];
      }
    }
  }

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      resultado[i][j] = temp[i][j];
    }
  }

  liberarMatriz(temp, n);
}

void calcularPotencia(long long **A, int n, int k, long long **resultado)
{
  long long **temp;
  crearMatriz(&temp, n, n);

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      temp[i][j] = (i == j) ? 1 : 0;
    }
  }

  long long **aux;

  crearMatriz(&aux, n, n);
  copiarMatriz(aux, A, n, n);

  while (k > 0)
  {
    if (k % 2 == 1)
    {
      multiplicarMatrices(temp, aux, temp, n);
    }
    multiplicarMatrices(aux, aux, aux, n);
    k /= 2;
  }

  copiarMatriz(resultado, temp, n, n);

  liberarMatriz(temp, n);
  liberarMatriz(aux, n);
}

void mostrarMatriz(long long **matriz, int filas, int columnas)
{
  for (int i = 0; i < filas; i++)
  {
    for (int j = 0; j < columnas; j++)
    {
      cout << matriz[i][j] << " ";
    }
    cout << endl;
  }
}

int main()
{
  const int n = 2;
  long long **A;
  long long **resultado;

  crearMatriz(&A, n, n);
  crearMatriz(&resultado, n, n);

  A[0][0] = 2;
  A[0][1] = 3;
  A[1][0] = 4;
  A[1][1] = 5;

  int k;
  cout << "Ingrese un numero natural: ";
  cin >> k;

  calcularPotencia(A, n, k, resultado);

  cout << "A ^" << k << " =" << endl;
  mostrarMatriz(resultado, n, n);

  liberarMatriz(A, n);
  liberarMatriz(resultado, n);

  return 0;
}