#include <iostream>

int *crearArreglo(int n)
{
  int *arr = new int[n];

  for (int i = 0; i < n; ++i)
  {
    arr[i] = (i + 1) * 10;
  }

  return arr;
}

int main()
{
  int n;
  std::cout << "Ingrese el tamaño del arreglo: ";
  std::cin >> n;

  int *arreglo = crearArreglo(n);

  std::cout << "Contenido del arreglo:" << std::endl;

  for (int i = 0; i < n; ++i)
  {
    std::cout << arreglo[i] << " ";
  }

  std::cout << std::endl;
  delete[] arreglo;

  return 0;
}
