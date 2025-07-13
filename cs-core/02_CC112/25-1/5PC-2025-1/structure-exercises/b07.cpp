#include <iostream>
#include <string>

// estructura Producto con nombre y precio
struct Producto
{
  std::string nombre;
  double precio;
};

int main()
{
  int numProductos;
  std::cout << "¿Cuántos productos desea ingresar? ";
  std::cin >> numProductos;

  Producto *productos = new Producto[numProductos];

  for (int i = 0; i < numProductos; i++)
  {
    std::cout << "\nProducto " << (i + 1) << ":" << std::endl;

    std::cout << "Nombre: ";
    std::cin.ignore();
    std::getline(std::cin, productos[i].nombre);

    std::cout << "Precio: $";
    std::cin >> productos[i].precio;
  }

  std::cout << "\n--- Lista de Productos ---" << std::endl;

  for (int i = 0; i < numProductos; i++)
  {
    std::cout << "Producto " << (i + 1) << ":" << std::endl;
    std::cout << "Nombre: " << productos[i].nombre << std::endl;
    std::cout << "Precio: $" << productos[i].precio << std::endl;
    std::cout << "------------------------" << std::endl;
  }

  delete[] productos;
  productos = nullptr;

  return 0;
}
