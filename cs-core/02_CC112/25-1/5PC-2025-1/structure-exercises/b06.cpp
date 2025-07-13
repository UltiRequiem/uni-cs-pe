#include <iostream>
#include <string>

using std::string;

struct Persona
{
  string nombre;
  int edad;
};

int main()
{
  Persona *personaPtr = new Persona;

  std::cout << "Ingrese el nombre: ";
  std::cin >> personaPtr->nombre;

  std::cout << "Ingrese la edad: ";
  std::cin >> personaPtr->edad;

  std::cout << "\nDatos de la persona:" << std::endl;
  std::cout << "Nombre: " << personaPtr->nombre << std::endl;
  std::cout << "Edad: " << personaPtr->edad << " años" << std::endl;

  delete personaPtr;
  personaPtr = nullptr;

  return 0;
}
