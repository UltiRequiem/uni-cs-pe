#include <iostream>
#include <cmath>
using namespace std;

class SeparadorDecimal {
private:
    double numeroCompleto;
    int parteEntera;
    double parteDecimal;
    
    // Función auxiliar para extraer la parte decimal
    void separarPartes() {
        parteEntera = static_cast<int>(floor(abs(numeroCompleto)));
        parteDecimal = abs(numeroCompleto) - parteEntera;
        
        // Mantener el signo en la parte entera si el número es negativo
        if(numeroCompleto < 0) {
            parteEntera = -parteEntera;
        }
    }

public:
    SeparadorDecimal(double num = 0.0) : numeroCompleto(num) {
        separarPartes();
    }
    
    void setNumero(double num) {
        numeroCompleto = num;
        separarPartes();
    }
    
    double getNumeroCompleto() const {
        return numeroCompleto;
    }
    
    int getParteEntera() const {
        return parteEntera;
    }
    
    double getParteDecimal() const {
        return parteDecimal;
    }
    
    void mostrarSeparacion() const {
        cout << "Número completo: " << numeroCompleto << endl;
        cout << "Parte entera: " << parteEntera << endl;
        cout << "Parte decimal: " << parteDecimal << endl;
    }
    
    // Función adicional para mostrar con más detalle
    void mostrarDetallado() const {
        cout << "Análisis del número " << numeroCompleto << ":" << endl;
        cout << "  ├─ Parte entera: " << parteEntera << endl;
        cout << "  └─ Parte decimal: " << parteDecimal << endl;
        
        if(numeroCompleto < 0) {
            cout << "  Nota: El número es negativo" << endl;
        }
    }
};

int main() {
    double numero;
    
    cout << "Ingrese un número con parte decimal: ";
    cin >> numero;
    
    SeparadorDecimal separador(numero);
    
    cout << "\n=== RESULTADO ===" << endl;
    separador.mostrarSeparacion();
    
    cout << "\n=== ANÁLISIS DETALLADO ===" << endl;
    separador.mostrarDetallado();
    
    // Ejemplo del enunciado
    cout << "\n=== EJEMPLO DEL ENUNCIADO ===" << endl;
    SeparadorDecimal ejemplo(234.23);
    ejemplo.mostrarDetallado();
    
    // Ejemplos adicionales
    cout << "\n=== EJEMPLOS ADICIONALES ===" << endl;
    double ejemplos[] = {-156.789, 42.0, 0.567, -0.123, 1000.001};
    
    for(double ej : ejemplos) {
        cout << "\n";
        SeparadorDecimal sep(ej);
        sep.mostrarDetallado();
    }
    
    return 0;
}
