#include <iostream>
using namespace std;

int main() {
    int n;

    cout << "Ingrese un número entero: ";
    cin >> n;

    cout << "Secuencia: ";
    
    while (n != 1) {
        cout << n << " ";
        if (n % 2 == 0) {
            n = n / 2;
            continue;
        } 
            n = 3 * n + 1;
    }
    
    cout << n << endl;

    return 0;
}