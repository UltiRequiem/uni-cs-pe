/*
[5.0 ptos.] Desarrolle una estructura llamada 'Estudiante' que contenga los
atributos 'nombre' y 'nota'. Posteriormente, cree un arreglo de tipo
'Estudiante' con capacidad para almacenar 'n' elementos. A continuación,
solicite al usuario ingresar los nombres y las notas de los 'n' estudiantes,
para luego imprimir el nombre y la nota del estudiante con la calificación más
alta.
*/

#include <iostream>
#include <string>

using namespace std;

struct Estudiante {
  string nombre;
  int nota;
};

int main() {
  Estudiante *students = nullptr;

  int n;

  cout << "Ingrese el número de estudiantes: ";
  cin >> n;

  students = new Estudiante[n];
  int bestStudentIndex = 0;

  for (int i = 0; i < n; i++) {
    cout << "Ingrese el nombre del estudiante " << (i + 1) << ": ";
    cin >> students[i].nombre;
    cout << "Ingrese la nota del estudiante " << (i + 1) << ": ";
    cin >> students[i].nota;

    if (i == 0) {
      bestStudentIndex = i;
    } else if (students[i].nota > students[bestStudentIndex].nota) {
      bestStudentIndex = i;
    }
  }

  cout << "El estudiante con la calificación más alta es: "
       << students[bestStudentIndex].nombre << " con una nota de "
       << students[bestStudentIndex].nota << endl;

  return 0;
}
