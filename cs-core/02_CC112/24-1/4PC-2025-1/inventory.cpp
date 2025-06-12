
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void concatenarArchivos(ifstream &archivo1, ifstream &archivo2,
                        ofstream &archivoSalida) {
  string linea;

  while (getline(archivo1, linea)) {
    archivoSalida << linea << endl;
  }

  while (getline(archivo2, linea)) {
    archivoSalida << linea << endl;
  }
}

int calcularSumaTotal(ifstream &archivo) {
  string linea;
  int suma = 0;

  while (getline(archivo, linea)) {
    try {
      suma += stoi(linea);
    } catch (...) {
    }
  }

  return suma;
}

int main() {
  string nombreArchivo1, nombreArchivo2;

  cout << "Ingrese el nombre del primer archivo: ";
  cin >> nombreArchivo1;

  cout << "Ingrese el nombre del segundo archivo: ";
  cin >> nombreArchivo2;

  ifstream archivo1(nombreArchivo1);
  ifstream archivo2(nombreArchivo2);

  if (!archivo1.is_open() || !archivo2.is_open()) {
    cerr << "Error al abrir uno de los archivos de entrada." << endl;
    return 1;
  }

  ofstream archivoSalida("inventario_total.txt");
  concatenarArchivos(archivo1, archivo2, archivoSalida);

  archivo1.close();
  archivo2.close();
  archivoSalida.close();

  ifstream archivoInventario("inventario_total.txt");
  int total = calcularSumaTotal(archivoInventario);
  archivoInventario.close();

  ofstream archivoInventarioFinal("inventario_total.txt", ios::app);
  archivoInventarioFinal << "TOTAL DE PRODUCTOS EN STOCK: " << total << endl;
  archivoInventarioFinal.close();

  cout << "Proceso completo: inventario total generado de forma exitosa"
       << endl;

  return 0;
}
