#include <iostream>
using namespace std;

class DosEnteros {
private:
    int valor1, valor2;

public:
    DosEnteros() : valor1(0), valor2(0) {}
    
    // Función miembro para ingresar valores desde teclado
    void ingresarValores() {
        cout << "Ingrese el primer valor entero: ";
        cin >> valor1;
        cout << "Ingrese el segundo valor entero: ";
        cin >> valor2;
    }
    
    // Función miembro para mostrar valores en pantalla
    void mostrarValores() const {
        cout << "Primer valor: " << valor1 << endl;
        cout << "Segundo valor: " << valor2 << endl;
        cout << "Suma: " << (valor1 + valor2) << endl;
    }
    
    // Métodos adicionales útiles
    int obtenerPrimero() const { return valor1; }
    int obtenerSegundo() const { return valor2; }
};

int main() {
    DosEnteros objeto;
    
    cout << "=== CLASE CON DOS VARIABLES ENTERAS ===" << endl;
    objeto.ingresarValores();
    
    cout << "\n=== VALORES INGRESADOS ===" << endl;
    objeto.mostrarValores();
    
    return 0;
}
