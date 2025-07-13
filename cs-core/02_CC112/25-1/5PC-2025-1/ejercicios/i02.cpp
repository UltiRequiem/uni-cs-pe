#include <iostream>
#include <cstring>

struct Estudiante
{
  char *nombre;
  int edad;
};

int main()
{
  Estudiante est;

  char buffer[100];

  std::cout << "Nombre: ";
  std::cin.getline(buffer, 100);

  est.nombre = new char[strlen(buffer) + 1];
  strcpy(est.nombre, buffer);

  std::cout << "Edad: ";
  std::cin >> est.edad;
  std::cout << "\nNombre: " << est.nombre << "\nEdad: " << est.edad << std::endl;

  delete[] est.nombre;

  return 0;
}
