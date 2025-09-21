#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class Empleado {
private:
    string nombre;
    double salario;

public:
    Empleado(string nom = "", double sal = 0.0) : nombre(nom), salario(sal) {}
    
    void ingresarDatos() {
        cout << "Ingrese nombre del empleado: ";
        getline(cin, nombre);
        cout << "Ingrese salario: ";
        cin >> salario;
        cin.ignore(); // Limpiar buffer para próxima lectura
    }
    
    void mostrarDatos() const {
        cout << left << setw(15) << nombre << setw(10) << salario << endl;
    }
    
    string getNombre() const { return nombre; }
    double getSalario() const { return salario; }
};

int main() {
    int numEmpleados;
    cout << "Ingrese el número de empleados: ";
    cin >> numEmpleados;
    cin.ignore(); // Limpiar buffer
    
    // Arreglo de objetos para almacenar empleados
    Empleado* empleados = new Empleado[numEmpleados];
    
    cout << "\n=== INGRESO DE DATOS ===" << endl;
    for(int i = 0; i < numEmpleados; i++) {
        cout << "\nEmpleado " << (i + 1) << ":" << endl;
        empleados[i].ingresarDatos();
    }
    
    cout << "\n=== LISTADO DE EMPLEADOS ===" << endl;
    cout << left << setw(15) << "Nombre" << setw(10) << "Salario" << endl;
    cout << string(25, '-') << endl;
    
    for(int i = 0; i < numEmpleados; i++) {
        empleados[i].mostrarDatos();
    }
    
    // Ejemplo con datos predefinidos como en el enunciado
    cout << "\n=== EJEMPLO DEL ENUNCIADO ===" << endl;
    Empleado ejemplos[3] = {
        Empleado("Abel", 2600),
        Empleado("Paul", 2000),
        Empleado("Raquel", 2100)
    };
    
    cout << left << setw(15) << "Nombre" << setw(10) << "Salario" << endl;
    cout << string(25, '-') << endl;
    for(int i = 0; i < 3; i++) {
        ejemplos[i].mostrarDatos();
    }
    
    delete[] empleados; // Liberar memoria dinámica
    return 0;
}
