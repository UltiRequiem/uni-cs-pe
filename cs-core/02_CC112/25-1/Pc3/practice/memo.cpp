/*
(a) Escriba un programa que lea el código y nota de varios alumnos y lo almacene
en una matriz de 2 columnas y una cantidad de filas que vaya aumentando a medida
que se ingresa los datos. (Para ello utilice la memoria dinámica) (2 ptos.) El
proceso termina cuando escribe "fin" en el código. (b) Recorriendo la matriz
creada, muestre la lista de los alumnos que obtuvieron la mayor nota. (3 ptos.)
Nota: Si no utiliza la memoria dinámica el puntaje es cero.
*/

#include <cctype>
#include <cmath> // Para fabs
#include <iostream>
#include <string>

using namespace std;

int main() {
  string **matriz = nullptr;
  int filas = 0;
  string entrada;

  while (true) {
    cout << "Ingrese codigo del alumno (o 'fin' para terminar): ";
    cin >> entrada;

    if (entrada == "fin") {
      break;
    }

    double nota;
    cout << "Ingrese nota del alumno: ";
    cin >> nota;

    string **nuevaMatriz = new string *[filas + 1];

    for (int i = 0; i < filas + 1; ++i) {
      nuevaMatriz[i] = new string[2];
    }

    for (int i = 0; i < filas; ++i) {
      nuevaMatriz[i][0] = matriz[i][0];
      nuevaMatriz[i][1] = matriz[i][1];
    }

    nuevaMatriz[filas][0] = entrada;
    nuevaMatriz[filas][1] = to_string(nota);

    if (matriz != nullptr) {
      for (int i = 0; i < filas; ++i) {
        delete[] matriz[i];
      }
      delete[] matriz;
    }

    matriz = nuevaMatriz;
    ++filas;
  }

  if (filas == 0) {
    cout << "No se ingresaron alumnos." << endl;
    return 0;
  }

  double mayorNota = stod(matriz[0][1]);
  for (int i = 1; i < filas; ++i) {
    double notaActual = stod(matriz[i][1]);
    if (notaActual > mayorNota) {
      mayorNota = notaActual;
    }
  }

  cout << "\nAlumnos con la mayor nota (" << mayorNota << "):" << endl;
  for (int i = 0; i < filas; ++i) {
    double notaActual = stod(matriz[i][1]);
    if (fabs(notaActual - mayorNota) < 1e-6) {
      cout << "- Codigo: " << matriz[i][0] << ", Nota: " << notaActual << endl;
    }
  }

  for (int i = 0; i < filas; ++i) {
    delete[] matriz[i];
  }

  delete[] matriz;

  return 0;
}
