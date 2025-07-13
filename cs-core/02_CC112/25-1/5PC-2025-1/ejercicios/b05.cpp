#include <iostream>

// funcion que devuelva un puntero a entero
int *createDynamicInt()
{
  // new para asignar memoria
  int *ptr = new int;

  *ptr = 100;
  return ptr;
}

int main()
{
  int *dynamicInt = createDynamicInt();

  std::cout << "El valor devuelto por la función es: " << *dynamicInt << std::endl;

  delete dynamicInt;
  dynamicInt = nullptr;

  return 0;
}
