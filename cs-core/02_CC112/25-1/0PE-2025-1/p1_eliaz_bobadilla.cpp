#include <iostream>
using namespace std;

int main() {
    int a, b, c;

    cout << "Ingrese tres números enteros: ";
    cin >> a >> b >> c;

    int mayor = max(a, max(b, c));
    int menor = min(a, min(b, c));

    bool esProgresionAritmetica = (b - a == c - b) || (c - b == a - c) || (a - c == b - a);

    cout << "El mayor número es: " << mayor << endl;
    cout << "El menor número es: " << menor << endl;

    if (esProgresionAritmetica) {
        cout << "Los números forman una progresión aritmética." << endl;
    } else {
        cout << "Los números no forman una progresión aritmética." << endl;
    }

    return 0;
}