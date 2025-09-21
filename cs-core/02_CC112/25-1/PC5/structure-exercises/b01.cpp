#include <iostream>

int main()
{
  // crear un puntero a entero
  int *ptr;

  // usamos new para asignar memoria dinámica
  ptr = new int;

  //  Asigna un valor al entero apuntado
  *ptr = 42;

  std::cout << "El valor del entero es: " << *ptr << std::endl;

  // delete
  delete ptr;

  // Buena practica
  ptr = nullptr;

  return 0;
}
