#include <iostream>

int main()
{
  int size;
  std::cout << "Ingrese el tamaño del arreglo: ";
  std::cin >> size;

  // new para crear un arreglo dinámico
  int *arr = new int[size];

  std::cout << "Ingrese " << size << " valores:" << std::endl;
  for (int i = 0; i < size; i++)
  {
    std::cout << "Elemento " << i << ": ";
    std::cin >> arr[i];
  }

  std::cout << "\nLos valores ingresados son:" << std::endl;
  for (int i = 0; i < size; i++)
  {
    std::cout << "Elemento " << i << ": " << arr[i] << std::endl;
  }

  // delete[] para liberar la memoria
  delete[] arr;

  // Buena practica
  arr = nullptr;

  return 0;
}
