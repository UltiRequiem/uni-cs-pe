#include <iostream>

int main()
{
  const int size = 5;
  int *arr = new int[size];

  for (int i = 0; i < size; i++)
  {
    arr[i] = i + 1;
  }

  std::cout << "Valores del arreglo:" << std::endl;
  for (int i = 0; i < size; i++)
  {
    std::cout << "arr[" << i << "] = " << arr[i] << std::endl;
  }

  delete[] arr;
  arr = nullptr;

  return 0;
}
