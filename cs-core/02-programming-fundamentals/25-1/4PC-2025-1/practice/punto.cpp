/*
Implemente una estructura llamada 'Punto' que defina las tres coordenadas (x, y,
z) de un punto en un espacio tridimensional. Luego, cree dos instancias de la
estructura 'Punto' y solicite al usuario ingresar las coordenadas de ambos
puntos desde el teclado. Calcule la distancia euclidiana entre los dos puntos y
muestre el resultado en pantalla.
*/

#include <cmath>
#include <iostream>

struct Point {
  int x;
  int y;
  int z;
};

int main() {
  Point p1, p2;

  std::cout << "Ingrese las coordenadas del primer punto (x, y, z): ";
  std::cin >> p1.x >> p1.y >> p1.z;
  std::cout << "Ingrese las coordenadas del segundo punto (x, y, z): ";
  std::cin >> p2.x >> p2.y >> p2.z;

  auto distance =
      sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) + pow(p2.z - p1.z, 2));

  std::cout << "La distancia euclidiana entre los dos puntos es: " << distance
            << std::endl;
  return 0;
}
