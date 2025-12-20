#include <iostream>

int main()
{
  int **ptrPtr;

  ptrPtr = new int *;

  *ptrPtr = new int;

  **ptrPtr = 200;

  std::cout << "Valor del entero a través del doble puntero: " << **ptrPtr << std::endl;

  delete *ptrPtr;
  delete ptrPtr;

  // asignar nullptr
  ptrPtr = nullptr;

  return 0;
}
