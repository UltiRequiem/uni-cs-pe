#include <iostream>

int main()
{
  //  arreglo dinamico de n elementos
  int n;
  std::cout << "Ingrese el tamaño inicial del arreglo: ";
  std::cin >> n;

  int *arr = new int[n];

  std::cout << "Ingrese " << n << " valores:" << std::endl;
  for (int i = 0; i < n; i++)
  {
    std::cout << "Elemento " << i << ": ";
    std::cin >> arr[i];
  }

  int newSize;
  std::cout << "\nIngrese el nuevo tamaño del arreglo (mayor que " << n << "): ";
  std::cin >> newSize;

  if (newSize <= n)
  {
    std::cout << "El nuevo tamaño debe ser mayor que el tamaño original." << std::endl;
    delete[] arr;
    arr = nullptr;
    return 1;
  }

  int *newArr = new int[newSize];

  // copia los valores antiguos al nuevo arreglo
  for (int i = 0; i < n; i++)
  {
    newArr[i] = arr[i];
  }

  for (int i = n; i < newSize; i++)
  {
    std::cout << "Nuevo elemento " << i << ": ";
    std::cin >> newArr[i];
  }

  delete[] arr;

  arr = newArr;

  std::cout << "\nArreglo con nuevo tamaño:" << std::endl;
  for (int i = 0; i < newSize; i++)
  {
    std::cout << "Elemento " << i << ": " << arr[i] << std::endl;
  }

  delete[] arr;
  arr = nullptr;

  return 0;
}
