#include <iostream>
#include <string>

using std::string;

// Estructura Libro con título y autora
struct Libro
{
  string titulo;
  string autor;
};

int main()
{
  int n;

  std::cout << "¿Cuántos libros? ";
  std::cin >> n;
  std::cin.ignore();

  Libro **libros = new Libro *[n];

  for (int i = 0; i < n; ++i)
  {
    libros[i] = new Libro;

    std::cout << "Libro " << (i + 1) << " título: ";
    std::getline(std::cin, libros[i]->titulo);

    if (libros[i]->titulo.empty())
    {
      std::cout << "Título no puede estar vacío. Intente de nuevo.\n";
      --i; // repite la iteracion actual
      delete libros[i];
      continue;
    }

    std::cout << "Autor: ";
    std::getline(std::cin, libros[i]->autor);

    if (libros[i]->autor.empty())
    {
      std::cout << "Autor no puede estar vacío. Intente de nuevo.\n";
      --i;
      delete libros[i];
      continue;
    }
  }

  std::cout << "\nLista de libros:\n";

  for (int i = 0; i < n; ++i)
  {
    std::cout << libros[i]->titulo << " de " << libros[i]->autor << std::endl;
    delete libros[i];
  }

  delete[] libros;
  return 0;
}
