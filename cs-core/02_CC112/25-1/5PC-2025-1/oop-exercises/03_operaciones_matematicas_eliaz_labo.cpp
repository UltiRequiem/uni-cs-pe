#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class OperacionesMatematicas {
private:
    int numero;
    string cadena;

public:
    OperacionesMatematicas() : numero(0), cadena("") {}
    
    void setNumero(int num) { numero = num; }
    void setCadena(const string& str) { cadena = str; }
    
    // Calcular factorial de un número
    long long calcularFactorial() {
        if(numero < 0) return -1; // Error para negativos
        long long factorial = 1;
        for(int i = 2; i <= numero; i++) {
            factorial *= i;
        }
        return factorial;
    }
    
    // Invertir un número entero
    int invertirNumero() {
        int original = abs(numero);
        int invertido = 0;
        
        while(original > 0) {
            invertido = invertido * 10 + original % 10;
            original /= 10;
        }
        
        return (numero < 0) ? -invertido : invertido;
    }
    
    // Verificar si un número es palíndromo
    bool esNumeroPalindromo() {
        return numero == invertirNumero();
    }
    
    // Verificar si una palabra es palíndromo
    bool esPalabraPalindroma() {
        string normalizada = "";
        for(char c : cadena) {
            if(isalnum(c)) {
                normalizada += tolower(c);
            }
        }
        
        string invertida = normalizada;
        reverse(invertida.begin(), invertida.end());
        return normalizada == invertida;
    }
    
    // Verificar si un número es perfecto
    bool esNumeroPerfecto() {
        if(numero <= 1) return false;
        
        int sumaDivisores = 1; // 1 siempre es divisor
        for(int i = 2; i * i <= numero; i++) {
            if(numero % i == 0) {
                sumaDivisores += i;
                if(i != numero / i) { // Evitar contar dos veces el mismo divisor
                    sumaDivisores += numero / i;
                }
            }
        }
        
        return sumaDivisores == numero;
    }
    
    // Verificar si es número de Armstrong
    bool esNumeroArmstrong() {
        int original = abs(numero);
        int numDigitos = to_string(original).length();
        int suma = 0;
        int temp = original;
        
        while(temp > 0) {
            int digito = temp % 10;
            int potencia = 1;
            for(int i = 0; i < numDigitos; i++) {
                potencia *= digito;
            }
            suma += potencia;
            temp /= 10;
        }
        
        return suma == original;
    }
    
    // Generar sucesión de Fibonacci
    void generarFibonacci() {
        if(numero <= 0) {
            cout << "Debe ingresar un número positivo." << endl;
            return;
        }
        
        cout << "Primeros " << numero << " términos de Fibonacci:" << endl;
        
        if(numero >= 1) cout << "0 ";
        if(numero >= 2) cout << "1 ";
        
        int a = 0, b = 1;
        for(int i = 3; i <= numero; i++) {
            int siguiente = a + b;
            cout << siguiente << " ";
            a = b;
            b = siguiente;
        }
        cout << endl;
    }
};

int main() {
    OperacionesMatematicas calc;
    int opcion, num;
    string palabra;
    
    do {
        cout << "\n=== OPERACIONES MATEMÁTICAS CON CLASES ===" << endl;
        cout << "1. Calcular factorial" << endl;
        cout << "2. Invertir número" << endl;
        cout << "3. Verificar número palíndromo" << endl;
        cout << "4. Verificar palabra palíndroma" << endl;
        cout << "5. Verificar número perfecto" << endl;
        cout << "6. Verificar número de Armstrong" << endl;
        cout << "7. Generar Fibonacci" << endl;
        cout << "0. Salir" << endl;
        cout << "Seleccione opción: ";
        cin >> opcion;
        
        switch(opcion) {
            case 1:
                cout << "Ingrese número: ";
                cin >> num;
                calc.setNumero(num);
                cout << "Factorial de " << num << " = " << calc.calcularFactorial() << endl;
                break;
                
            case 2:
                cout << "Ingrese número: ";
                cin >> num;
                calc.setNumero(num);
                cout << "Número invertido: " << calc.invertirNumero() << endl;
                break;
                
            case 3:
                cout << "Ingrese número: ";
                cin >> num;
                calc.setNumero(num);
                cout << num << (calc.esNumeroPalindromo() ? " ES" : " NO es") << " palíndromo" << endl;
                break;
                
            case 4:
                cout << "Ingrese palabra: ";
                cin >> palabra;
                calc.setCadena(palabra);
                cout << "\"" << palabra << "\"" << (calc.esPalabraPalindroma() ? " ES" : " NO es") << " palíndroma" << endl;
                break;
                
            case 5:
                cout << "Ingrese número: ";
                cin >> num;
                calc.setNumero(num);
                cout << num << (calc.esNumeroPerfecto() ? " ES" : " NO es") << " perfecto" << endl;
                break;
                
            case 6:
                cout << "Ingrese número: ";
                cin >> num;
                calc.setNumero(num);
                cout << num << (calc.esNumeroArmstrong() ? " ES" : " NO es") << " de Armstrong" << endl;
                break;
                
            case 7:
                cout << "¿Cuántos términos? ";
                cin >> num;
                calc.setNumero(num);
                calc.generarFibonacci();
                break;
                
            case 0:
                cout << "¡Hasta luego!" << endl;
                break;
                
            default:
                cout << "Opción inválida" << endl;
        }
        
    } while(opcion != 0);
    
    return 0;
}
