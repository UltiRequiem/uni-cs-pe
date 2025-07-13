#include <iostream>

int main()
{
  // asignamos memoria con new
  int *ptr = new int;
  *ptr = 42;

  std::cout << "Valor antes de delete: " << *ptr << std::endl;

  // libera la memoria con delete
  delete ptr;

  std::cout << "Intentando acceder al valor después de delete..." << std::endl;
  std::cout << "Valor después de delete: " << *ptr << std::endl;

  std::cout << "\n--- Explicación ---" << std::endl;
  std::cout << "El comportamiento observado es indefinido. Después de usar delete:" << std::endl;
  std::cout << "- El puntero sigue apuntando a la misma dirección" << std::endl;
  std::cout << "- La memoria ha sido liberada y puede ser reutilizada" << std::endl;
  std::cout << "- Acceder a ella puede causar errores impredecibles o crashes" << std::endl;
  std::cout << "- Puede mostrar el mismo valor, un valor corrupto, o causar un segmentation fault" << std::endl;
  std::cout << "- Es importante asignar nullptr después de delete para evitar este problema" << std::endl;

  ptr = nullptr;

  return 0;
}
