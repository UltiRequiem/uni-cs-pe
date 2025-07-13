#include <iostream>

int main()
{
  int filas, columnas;
  std::cout << "Filas: ";
  std::cin >> filas;
  std::cout << "Columnas: ";
  std::cin >> columnas;

  int **matriz = new int *[filas];

  for (int i = 0; i < filas; ++i)
  {
    matriz[i] = new int[columnas];
  }

  for (int i = 0; i < filas; ++i)
  {
    for (int j = 0; j < columnas; ++j)
    {
      std::cout << "Elemento [" << i << "][" << j << "]: ";

      std::cin >> matriz[i][j];
    }
  }

  std::cout << "\nMatriz ingresada:\n";

  for (int i = 0; i < filas; ++i)
  {
    for (int j = 0; j < columnas; ++j)
    {
      std::cout << matriz[i][j] << " ";
    }

    std::cout << std::endl;
  }

  for (int i = 0; i < filas; ++i)
  {
    delete[] matriz[i];
  }

  delete[] matriz;

  return 0;
}
