#include <iostream>
using namespace std;

class Numero {
private:
    int dato;

public:
    Numero(int valor = 0) : dato(valor) {}
    
    // Función para inicializar el dato
    void inicializar(int valor) {
        dato = valor;
    }
    
    // Función constante para cambiar el dato (debe ser constante según enunciado)
    void cambiar(int nuevoValor) const {
        // Nota: Esta función debería ser const según el enunciado,
        // pero no puede modificar dato si es const. Implementación alternativa:
        cout << "Valor anterior: " << dato << ", Nuevo valor solicitado: " << nuevoValor << endl;
        cout << "Nota: Esta función es const y no puede modificar el dato." << endl;
    }
    
    // Función alternativa no const para cambiar realmente el dato
    void cambiarValor(int nuevoValor) {
        dato = nuevoValor;
    }
    
    // Función para mostrar el dato
    void mostrar() const {
        cout << "El valor actual es: " << dato << endl;
    }
    
    int obtenerDato() const {
        return dato;
    }
};

int main() {
    Numero num;
    int valor;
    
    cout << "=== INICIALIZACIÓN ===" << endl;
    cout << "Ingrese un valor inicial: ";
    cin >> valor;
    num.inicializar(valor);
    num.mostrar();
    
    cout << "\n=== INTENTO DE CAMBIO CON FUNCIÓN CONST ===" << endl;
    cout << "Ingrese nuevo valor: ";
    cin >> valor;
    num.cambiar(valor); // Esta función es const y no puede modificar
    num.mostrar();
    
    cout << "\n=== CAMBIO REAL DEL VALOR ===" << endl;
    cout << "Ingrese otro valor para cambio real: ";
    cin >> valor;
    num.cambiarValor(valor);
    num.mostrar();
    
    return 0;
}
