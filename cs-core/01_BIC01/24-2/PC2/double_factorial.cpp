// ELIAZ BOBADILLA CAMARENA 20244697E

#include <iostream>

using namespace std;

unsigned long long dobleFactorial(int n) {
	unsigned long long resultado = 1;

	for (int i = n; i > 0; i -= 2) {
		resultado *= i;
	}

	return resultado;
}

int main() {
	int n;

	cout << "Ingresa un número entero positivo: ";
	cin >> n;

	if (n <= 0) {
		cout << "El número debe ser positivo." << endl;
	} else {
		cout << "El doble factorial de " << n << " es: " << dobleFactorial(n) << endl;
	}

	return 0;
}

