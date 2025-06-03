#include <iostream>
using namespace std;

const int MAX = 100;

void mappa(int **mapa, bool **visitado, int filas, int columnas, int x, int y)
{
  if (x < 0 || x >= filas || y >= columnas || visitado[x][y] || mapa[x][y] == 1 || y < 0)
  {
    return;
  }

  visitado[x][y] = true;

  mappa(mapa, visitado, filas, columnas, x - 1, y);
  mappa(mapa, visitado, filas, columnas, x + 1, y);
  mappa(mapa, visitado, filas, columnas, x, y - 1);
  mappa(mapa, visitado, filas, columnas, x, y + 1);
}

int main()
{
  int filas, columnas;
  cout << "Ingrese el número de filas y columnas del mapa: ";
  cin >> filas >> columnas;

  if (filas > MAX || columnas > MAX)
  {
    cout << "Dimensiones exceden el máximo permitido de " << MAX << "x" << MAX << endl;
    return 1;
  }

  int **mapa = new int *[filas];
  for (int i = 0; i < filas; ++i)
  {
    mapa[i] = new int[columnas];
  }

  bool **visitado = new bool *[filas];
  for (int i = 0; i < filas; ++i)
  {
    visitado[i] = new bool[columnas];
    for (int j = 0; j < columnas; ++j)
      visitado[i][j] = false;
  }

  cout << "Ingrese los valores del mapa (0 = camino, 1 = obstáculo):\n";
  for (int i = 0; i < filas; ++i)
  {
    for (int j = 0; j < columnas; ++j)
    {
      cin >> mapa[i][j];
    }
  }

  int regiones = 0;

  for (int i = 0; i < filas; ++i)
  {
    for (int j = 0; j < columnas; ++j)
    {
      if (mapa[i][j] == 0 && !visitado[i][j])
      {
        mappa(mapa, visitado, filas, columnas, i, j);
        regiones++;
      }
    }
  }

  cout << "Mapa ingresado:\n";
  for (int i = 0; i < filas; ++i)
  {
    for (int j = 0; j < columnas; ++j)
    {
      cout << mapa[i][j];
    }
    cout << endl;
  }
  // ELIAZ SEBASTIAN BOBADILLA CAMARENA 20244697E

  cout << "Número de regiones transitables conectadas: " << regiones << endl;

  for (int i = 0; i < filas; ++i)
  {
    delete[] mapa[i];
    delete[] visitado[i];
  }
  delete[] mapa;
  delete[] visitado;

  return 0;
}
