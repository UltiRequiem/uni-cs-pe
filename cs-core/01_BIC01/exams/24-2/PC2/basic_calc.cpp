// ELIAZ BOBADILLA 20244697E

#include <iostream>

using namespace std;

int main() {
	double firstNumber, secondNumber;
	char operation;

	cout << "Ingresa dos numeros: ";
	cin >> firstNumber >> secondNumber;

	cout << "Ingresa la operacion a realizar (+, -, *, /, %): ";
	cin >> operation;

	if (operation == '+') {
		cout << "Resultado: " << firstNumber + secondNumber << endl;
	} else if (operation == '-') {
		cout << "Resultado: " << firstNumber - secondNumber << endl;
	} else if (operation == '*') {
		cout << "Resultado: " << firstNumber * secondNumber << endl;
	} else if (operation == '/') {
		if (secondNumber == 0) {
			cout << "Error: División por cero es una operacion no permitida." << endl;
		} else {
			cout << "Resultado: " << firstNumber / secondNumber << endl;
		}
	} else if (operation == '%') {
		if (secondNumber == 0) {
			cout << "Error: División por cero es una operacion no permitida." << endl;
		} else {
       		        cout << "Resultado: " << static_cast<int>(firstNumber) % static_cast<int>(secondNumber) << endl;
		}
	} else {
		cout << "Error: Operador no válido." << endl;
	}

	return 0;
}
