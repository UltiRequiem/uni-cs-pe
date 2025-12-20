#include <iostream>
using namespace std;

int main() {
    double ingreso, impuesto = 0, descuento = 0, impuestoFinal;

    cout << "Ingrese su ingreso anual: ";
    cin >> ingreso;

    if (ingreso <= 10000) {
        impuesto = 0;
    } else if (ingreso <= 30000) {
        impuesto = (ingreso - 10000) * 0.10;
    } else if (ingreso <= 60000) {
        impuesto = (30000 - 10000) * 0.10 + (ingreso - 30000) * 0.15;
    } else {
        impuesto = (30000 - 10000) * 0.10 + (60000 - 30000) * 0.15 + (ingreso - 60000) * 0.20;
    }

    if (ingreso > 100000) {
        descuento = impuesto * 0.10;
    } else if (ingreso > 50000) {
        descuento = impuesto * 0.05;
    }

    impuestoFinal = impuesto - descuento;

    cout << "El impuesto total a pagar antes del descuento es: " << impuesto << endl;
    cout << "El descuento aplicado es: " << descuento << endl;
    cout << "El impuesto total a pagar después del descuento es: " << impuestoFinal << endl;

    return 0;
}

