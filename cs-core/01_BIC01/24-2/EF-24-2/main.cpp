#include <iostream>
using namespace std;

int sumaMaxima(int A[], int n, int S) {
    int maxSuma = 0;

    // 2^n iteraciones
    for (int i = 0; i < (1 << n); i++) {
        int sumaActual = 0;
        
        for (int j = 0; j < n; j++) {

            // si es que tienen algun bit en común
            // entonces sumar el valor de A[j]
            if (i & (1 << j)) {
                sumaActual += A[j];
            }
        }

        // actualiza la suma
        if (sumaActual <= S && sumaActual > maxSuma) {
            maxSuma = sumaActual;
        }
    }

    return maxSuma;
}

int main() {
    int A[] = {3, 34, 4, 12, 5, 2};
    int S;

    cout << "Ingrese el valor de S: ";
    cin >> S;

    int n = sizeof(A) / sizeof(A[0]);
    int resultado = sumaMaxima(A, n, S);

    cout << "La suma máxima que no supera a " << S << " es " << resultado << endl;

    return 0;
}
