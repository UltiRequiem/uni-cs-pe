#include <iostream>

using namespace std;

int main(){
	int hoursWorked, hourPayRate, toPay = 0;

	cout << "How many hours have you worked? ";
	cin >> hoursWorked;

	cout << "What's your pay/hour? ";
	cin >> hourPayRate;

	if (hoursWorked <= 40) {
		toPay = hourPayRate * hourPayRate;
	} else {
		toPay = 40 * hourPayRate + (hoursWorked - 40)* hourPayRate *2;
	}

	cout << "Your expected salary is " << toPay << endl;

	return 0;
}
