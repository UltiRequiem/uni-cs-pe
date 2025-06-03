/*
Escriba código en C++, que asigne memoria dinámica para tres matrices 2 × 2 de
números de punto flotante de doble precisión, A, B y C. Asigne valores a las
entradas de A y B. Sea C = A + B. Amplíe su código para que calcule las entradas
de C, y luego imprima las entradas de C en la pantalla. Por último, desasigne la
memoria.
*/

#include <iostream>
using namespace std;

int main() {
  // Asignar memoria dinámica para las matrices A, B y C (2x2)
  double **A = new double *[2];
  double **B = new double *[2];
  double **C = new double *[2];

  for (int i = 0; i < 2; ++i) {
    A[i] = new double[2];
    B[i] = new double[2];
    C[i] = new double[2];
  }

  // Asignar valores a las entradas de A y B
  A[0][0] = 1.5;
  A[0][1] = 2.3;
  A[1][0] = 3.7;
  A[1][1] = 4.1;

  B[0][0] = 0.2;
  B[0][1] = 5.1;
  B[1][0] = 1.8;
  B[1][1] = 3.3;

  // Calcular C = A + B
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      C[i][j] = A[i][j] + B[i][j];
    }
  }

  // Imprimir las entradas de C
  cout << "Matriz C (Resultado de A + B):" << endl;
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      cout << C[i][j] << " ";
    }
    cout << endl;
  }

  // Desasignar la memoria
  for (int i = 0; i < 2; ++i) {
    delete[] A[i];
    delete[] B[i];
    delete[] C[i];
  }

  delete[] A;
  delete[] B;
  delete[] C;

  return 0;
}
