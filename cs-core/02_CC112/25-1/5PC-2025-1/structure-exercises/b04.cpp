#include <iostream>

int main()
{
  float *ptrFloat;

  ptrFloat = new float;

  *ptrFloat = 3.14159;

  std::cout << "El valor del float es: " << *ptrFloat << std::endl;

  // libera la memoria
  delete ptrFloat;
  ptrFloat = nullptr;

  return 0;
}
