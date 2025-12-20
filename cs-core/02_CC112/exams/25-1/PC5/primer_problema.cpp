#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept>

using std::string;
using std::to_string;
using std::pow;
using std::cout;
using std::cin;
using std::endl;
using std::invalid_argument;

class CuentaBancaria{
    public:
    string titular;
    double saldo;
    int numeroCuento;
    int transaccionesDelDia;
    
    CuentaBancaria(string titular, double saldo, int numeroCuenta)
        : titular(titular), saldo(saldo), numeroCuento(numeroCuenta), transaccionesDelDia(0) {}


    void retirar(double cantidad){
        if (transaccionesDelDia >= 3) {
            throw invalid_argument("No se pueden realizar mas de 3 retiros por dia.");
        }
        
        if (cantidad <= 0) {
            throw invalid_argument("La cantidad a retirar debe ser positiva.");
        }
        
        if (cantidad > saldo) {
            throw invalid_argument("Saldo insuficiente para realizar el retiro.");
        }
        
        saldo -= cantidad;
        transaccionesDelDia++;
    }


    void depositar(double cantidad){
        if (cantidad <= 0) {
            throw invalid_argument("La cantidad a depositar debe ser positiva.");
        }
        
        saldo += cantidad;
    }

    void mostrarSaldo() const {
        cout << "El saldo actual de la cuenta " << numeroCuento << " de " << titular << " es: " << saldo << endl;
    }

    void mostrarTransacciones() const {
        cout << "Numero de transacciones del dia: " << transaccionesDelDia << endl;
        if (transaccionesDelDia == 0) {
            cout << "No se han realizado transacciones hoy." << endl;
        } else {
            cout << "Se han realizado " << transaccionesDelDia << " transacciones hoy." << endl;
        }
    }

    void reiniciarTransacciones() {
        transaccionesDelDia = 0;
    }
};

int main(){
    string titular;
    double saldoInicial;
    int numeroCuenta;

    cout << "Ingrese el nombre del titular de la cuenta: ";
    cin >> titular;
    
    cout << "Ingrese el saldo inicial de la cuenta: ";
    cin >> saldoInicial;

    cout << "Ingrese el numero de cuenta: ";
    cin >> numeroCuenta;

    CuentaBancaria cuenta(titular, saldoInicial, numeroCuenta);

    int opcion;
    do {
        cout << "Menu de opciones:\n";
        cout << "1. Retirar dinero\n";
        cout << "2. Depositar dinero\n";
        cout << "3. Mostrar saldo y transacciones del dia\n";
        cout << "4. Reiniciar transacciones del dia\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                double cantidad;
                cout << "Ingrese la cantidad a retirar: ";
                cin >> cantidad;
                
                try {
                    cuenta.retirar(cantidad);
                } catch (const invalid_argument& e) {
                    cout << e.what() << endl;
                }
                
                break;
            }
            case 2: {
                double cantidad;
                cout << "Ingrese la cantidad a depositar: ";
                cin >> cantidad;
                
                try {
                    cuenta.depositar(cantidad);
                } catch (const invalid_argument& e) {
                    cout << e.what() << endl;
                }

                break;
            }
            case 3:
                cuenta.mostrarSaldo();
                cuenta.mostrarTransacciones();
                break;
            case 4:
                cuenta.reiniciarTransacciones();
                cout << "Transacciones del dia reiniciadas." << endl;
                break;
            case 5:
                cout << "Saliendo del programa." << endl;
                break;
            default:
                cout << "Opcion invalida. Intente nuevamente." << endl;
        }
    } while (opcion != 5);

    cout << "Tenga un buen dia, gracias por usar sistemas UNI" << endl;

    return 0;
}