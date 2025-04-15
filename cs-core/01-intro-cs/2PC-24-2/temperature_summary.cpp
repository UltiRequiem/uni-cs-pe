// ELIAZ BOBADILLA 20244697E

#include <iostream>

using namespace std;

int main() {
    const int DIAS = 7;

    double temperaturas[DIAS], suma = 0.0, promedio;

    for (int i = 1; i <= DIAS; i++) {
        cout << "Día " << i << ": ";
        cin >> temperaturas[i];
        suma += temperaturas[i];
    }

    promedio = suma / DIAS;

    cout << "La temperatura promedio es: " << promedio << " grados C" << endl;

    cout << "Temperatura promedio: ";

    if (promedio < 15) {
        cout << "Baja." << endl;
    } else if (promedio <= 25) {
        cout << "Normal." << endl;
    } else {
        cout << "Alta." << endl;
    }

    return 0;
}



