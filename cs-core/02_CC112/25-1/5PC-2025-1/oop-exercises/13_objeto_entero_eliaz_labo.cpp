#include <iostream>
using namespace std;

class NumeroEntero {
private:
    int valor;

public:
    NumeroEntero(int val = 0) : valor(val) {}
    
    void setValor(int val) {
        valor = val;
    }
    
    int getValor() const {
        return valor;
    }
    
    // Función miembro que devuelve un objeto de esta clase
    NumeroEntero obtenerObjeto() const {
        NumeroEntero nuevoObjeto(valor);
        return nuevoObjeto;
    }
    
    // Función adicional que demuestra operaciones con objetos
    NumeroEntero duplicar() const {
        return NumeroEntero(valor * 2);
    }
    
    NumeroEntero sumar(int incremento) const {
        return NumeroEntero(valor + incremento);
    }
    
    void mostrar() const {
        cout << "Valor: " << valor << endl;
    }
};

int main() {
    int numero;
    cout << "Ingrese un número entero: ";
    cin >> numero;
    
    NumeroEntero obj1(numero);
    cout << "Objeto original: ";
    obj1.mostrar();
    
    // Usando la función que devuelve un objeto de la misma clase
    NumeroEntero obj2 = obj1.obtenerObjeto();
    cout << "Objeto obtenido mediante función miembro: ";
    obj2.mostrar();
    
    // Demostrando operaciones adicionales
    NumeroEntero obj3 = obj1.duplicar();
    cout << "Objeto duplicado: ";
    obj3.mostrar();
    
    NumeroEntero obj4 = obj1.sumar(10);
    cout << "Objeto con suma de 10: ";
    obj4.mostrar();
    
    return 0;
}
