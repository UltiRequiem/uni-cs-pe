#include <iostream>
using namespace std;

int main() {
    double saldo = 0.0; 
    int opcion;

    do {
        cout << "\n--- Cajero Automático ---" << endl;
        cout << "1. Consultar saldo" << endl;
        cout << "2. Depositar dinero" << endl;
        cout << "3. Retirar dinero" << endl;
        cout << "4. Salir" << endl;
        cout << "Ingrese una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: 
                cout << "Su saldo actual es: $" << saldo << endl;
                break;

            case 2: { 
                double deposito;
                
                cout << "Ingrese la cantidad a depositar: $";
                cin >> deposito;
                
                if (deposito > 0) {
                    saldo += deposito;
                    cout << "Depósito exitoso. Su nuevo saldo es: $" << saldo << endl;
                    break;
                } 
                
                cout << "Cantidad inválida. Intente nuevamente." << endl;
                
                  
                break;
            }

            case 3: { 
                double retiro;
                
                cout << "Ingrese la cantidad a retirar: $";
                cin >> retiro;

                if (retiro > 0 && retiro <= saldo) {
                    saldo -= retiro;
                    cout << "Retiro exitoso. Su nuevo saldo es: $" << saldo << endl;
                    break;
                } 
                
                if (retiro > saldo) {
                    cout << "Fondos insuficientes. Su saldo actual es: $" << saldo << endl;
                    break;
                } 
                
                cout << "Cantidad inválida. Intente nuevamente." << endl;
                
                break;
            }

            case 4: // Exit
                cout << "Gracias por usar el cajero automático. ¡Hasta luego!" << endl;
                break;

            default: // Invalid option
                cout << "Opción no válida. Intente nuevamente." << endl;
        }
    } while (opcion != 4);

    cout << "Chao!" << endl;

    return 0;
}