// Eliaz bobadilla, 20244697E

#include <iostream>
using namespace std;

int main(){
    int input;
    
    cout << "Introduce un numero entero entre 1 y 20 (N): ";
    cin >> input;
    
    if (input < 1 or input > 20){
        cout << "Por favor ingrese un numero en el rango sugerido.";
        
        return 0;
    }
    
    cout << "Los primeros " << input << " números triangulares son:" <<endl;
    
    for (int curr = 1; curr <= input; curr++){
        cout << "T(" << curr*(curr +1)/2 << ")" << endl;
    }
    
    return 0;
}
