#include <iostream>
using std::cout, std::endl;

double reverseDivision(int number) {
    if (number == 1) return 1; 
    
    if (number % 2 == 0) {
        return 1.0 / (number + reverseDivision(number - 1));
    } 
    
        return number - reverseDivision(number - 1);
    
}

int main() {
    int n = 7; 

    cout << "Valor de n: " << n << endl;
    cout << "Resultado de reverseDivision(n): " << reverseDivision(n) << endl;

    return 0;
}