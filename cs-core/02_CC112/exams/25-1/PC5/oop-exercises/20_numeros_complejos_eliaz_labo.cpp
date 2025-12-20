#include <iostream>
#include <cmath>
using namespace std;

class NumeroComplejo {
private:
    double real;
    double imaginario;

public:
    NumeroComplejo(double r = 0.0, double i = 0.0) : real(r), imaginario(i) {}
    
    void setComplejo(double r, double i) {
        real = r;
        imaginario = i;
    }
    
    double getReal() const { return real; }
    double getImaginario() const { return imaginario; }
    
    void ingresarComplejo(const string& nombre) {
        cout << "Ingrese la parte real de " << nombre << ": ";
        cin >> real;
        cout << "Ingrese la parte imaginaria de " << nombre << ": ";
        cin >> imaginario;
    }
    
    // Método para sumar dos números complejos
    NumeroComplejo sumar(const NumeroComplejo& otro) const {
        double sumaReal = real + otro.real;
        double sumaImaginario = imaginario + otro.imaginario;
        return NumeroComplejo(sumaReal, sumaImaginario);
    }
    
    // Método para restar dos números complejos
    NumeroComplejo restar(const NumeroComplejo& otro) const {
        double restaReal = real - otro.real;
        double restaImaginario = imaginario - otro.imaginario;
        return NumeroComplejo(restaReal, restaImaginario);
    }
    
    void mostrarComplejo() const {
        if(imaginario >= 0) {
            cout << real << " + " << imaginario << "i";
        } else {
            cout << real << " - " << abs(imaginario) << "i";
        }
    }
    
    // Métodos adicionales útiles
    double modulo() const {
        return sqrt(real * real + imaginario * imaginario);
    }
    
    NumeroComplejo conjugado() const {
        return NumeroComplejo(real, -imaginario);
    }
};

int main() {
    NumeroComplejo num1, num2;
    
    cout << "=== INGRESO DE NÚMEROS COMPLEJOS ===" << endl;
    num1.ingresarComplejo("primer número");
    cout << endl;
    num2.ingresarComplejo("segundo número");
    
    cout << "\n=== NÚMEROS INGRESADOS ===" << endl;
    cout << "Primer número: ";
    num1.mostrarComplejo();
    cout << endl;
    cout << "Segundo número: ";
    num2.mostrarComplejo();
    cout << endl;
    
    cout << "\n=== OPERACIONES ===" << endl;
    
    // Suma
    NumeroComplejo suma = num1.sumar(num2);
    cout << "Suma: ";
    suma.mostrarComplejo();
    cout << endl;
    
    // Resta
    NumeroComplejo resta = num1.restar(num2);
    cout << "Resta: ";
    resta.mostrarComplejo();
    cout << endl;
    
    // Información adicional
    cout << "\n=== INFORMACIÓN ADICIONAL ===" << endl;
    cout << "Módulo del primer número: " << num1.modulo() << endl;
    cout << "Módulo del segundo número: " << num2.modulo() << endl;
    
    cout << "Conjugado del primer número: ";
    num1.conjugado().mostrarComplejo();
    cout << endl;
    
    cout << "Conjugado del segundo número: ";
    num2.conjugado().mostrarComplejo();
    cout << endl;
    
    return 0;
}
