// ELIAZ BOBADILLA 20244697E

#include <iostream>
#include <cmath>

using namespace std;

double funcion(float x, float y) {
	if (y == 1) {
		return x / (5 + log2(x));
	} else if (y == 2) {
		return pow(x, x) + sqrt(x);
	} else if (y == 3 || y == 4) {
		return 6 * x / (2 + x * y);
	} 

	return 1 + y*y;
}

int main() {
	float x, y;

	cout << "Ingresa el valor de x, y: ";
	cin >> x >> y;

	cout << "El resultado de la función es: " << funcion(x, y) << endl;

	return 0;
}

