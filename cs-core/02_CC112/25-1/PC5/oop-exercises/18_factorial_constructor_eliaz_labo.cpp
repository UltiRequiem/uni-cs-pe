#include <iostream>
using namespace std;

class Factorial {
private:
    int numero;
    long long resultado;
    
    // Función auxiliar para calcular factorial recursivamente
    long long calcularFactorial(int n) {
        if(n <= 1) return 1;
        return n * calcularFactorial(n - 1);
    }

public:
    // Constructor por defecto que inicializa con 0
    Factorial() : numero(0), resultado(1) {
        cout << "Constructor por defecto llamado. Número inicializado en 0." << endl;
    }
    
    // Constructor con parámetro
    Factorial(int num) : numero(num) {
        if(numero < 0) {
            cout << "No se puede calcular factorial de número negativo. Se establece en 0." << endl;
            numero = 0;
            resultado = 1;
        } else {
            resultado = calcularFactorial(numero);
        }
    }
    
    void setNumero(int num) {
        if(num < 0) {
            cout << "No se puede calcular factorial de número negativo." << endl;
            return;
        }
        numero = num;
        resultado = calcularFactorial(numero);
    }
    
    int getNumero() const {
        return numero;
    }
    
    long long getFactorial() const {
        return resultado;
    }
    
    void mostrarResultado() const {
        cout << "Factorial de " << numero << " = " << resultado << endl;
    }
    
    // Función adicional para mostrar el proceso de cálculo
    void mostrarProceso() const {
        cout << numero << "! = ";
        for(int i = numero; i > 0; i--) {
            cout << i;
            if(i > 1) cout << " × ";
        }
        cout << " = " << resultado << endl;
    }
};

int main() {
    // Usando constructor por defecto
    cout << "=== CONSTRUCTOR POR DEFECTO ===" << endl;
    Factorial factDefault;
    factDefault.mostrarResultado();
    
    // Ingresando un número
    int num;
    cout << "\n=== CÁLCULO DE FACTORIAL ===" << endl;
    cout << "Ingrese un número para calcular su factorial: ";
    cin >> num;
    
    Factorial factUsuario(num);
    factUsuario.mostrarResultado();
    factUsuario.mostrarProceso();
    
    // Ejemplos adicionales
    cout << "\n=== EJEMPLOS ADICIONALES ===" << endl;
    int ejemplos[] = {5, 7, 10, 0, 1};
    
    for(int ejemplo : ejemplos) {
        Factorial factEjemplo(ejemplo);
        factEjemplo.mostrarProceso();
    }
    
    return 0;
}
