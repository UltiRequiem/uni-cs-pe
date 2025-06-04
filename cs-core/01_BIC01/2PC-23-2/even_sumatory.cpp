#include <iostream>

using namespace std;

int evenSummation(int top){
	int result = 0;

	for (int i = 0; i <= top; i+=2){
		result += i;
	}

	return result;
}

int main(){
	int top = 0;

	cout << "Hasta que numero quieres sumar los pares? ";
	cin >> top;

	cout << "El resultado es: " << evenSummation(top) << endl;

	return 0;
}

