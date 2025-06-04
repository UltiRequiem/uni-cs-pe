/*
[5.0 ptos.] Una empresa al efectuar una venta registra el monto de la operación
y el código del vendedor (un entero entre 1 y 99). El usuario termina el ingreso
de datos ingresando un monto negativo para la venta. Escriba un programa de C++
que genere un arreglo dinámico con los códigos de los vendedores que superan el
promedio de ventas y muestre también el monto vendido por cada uno de ellos.
*/

#include <iostream>

using namespace std;

struct Venta {
  int valor;
  int codigoVendedor;
};

int main() {
  Venta *ventas = nullptr;
  int size = 0;

  while (true) {
    Venta venta;

    cout << "Ingrese el monto de la venta (negativo para terminar): ";

    cin >> venta.valor;

    if (venta.valor < 0) {
      break;
    }

    cout << "Ingrese el código del vendedor (1-99): ";
    cin >> venta.codigoVendedor;

    if (size == 0) {
      ventas = new Venta[1];
      ventas[0] = venta;
      size = 1;
      continue;
    }

    Venta *newSales = new Venta[size + 1];

    for (int j = 0; j < size; j++) {
      newSales[j] = ventas[j];
    }

    newSales[size] = venta;
    delete[] ventas;
    ventas = newSales;
    size++;
  }

  int totalSum = 0;

  for (int i = 0; i < size; i++) {
    totalSum += ventas[i].valor;
  }

  int average = (size > 0) ? totalSum / size : 0;

  cout << "Best sellers" << endl;

  for (int j = 0; j < size; j++) {
    if (ventas[j].valor > average) {
      cout << "Vendedor: " << ventas[j].codigoVendedor
           << ", Monto vendido: " << ventas[j].valor << endl;
    }
  }

  return 0;
}
