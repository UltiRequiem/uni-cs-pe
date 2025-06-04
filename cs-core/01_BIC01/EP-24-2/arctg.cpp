// Eliaz bobadilla, 20244697E

#include <iostream>
#include <cmath>

using namespace std;

int main(){
    float x;
    cout << "Ingrese el valor de x (|x| <= 1): ";
    cin >> x;
    
    if (not (abs(x) <= 1)){
        cout << "Porfavor ingrese un numero en el rango.";
        return 0;
    }
    
    float lastTerm =  x;
    float result = 0;
    int sign = 1;

    for (int i = 1; abs(lastTerm) > 1e-7; i +=2){
        lastTerm = pow(x,i)/i;
        if (sign == 1){
            result += lastTerm;
            sign = -1;
        } else {
            result -= lastTerm;
            sign = 1;
        }
    }
    
    cout << "El valor aproximado es: " << result;
    
    return 0;
}
