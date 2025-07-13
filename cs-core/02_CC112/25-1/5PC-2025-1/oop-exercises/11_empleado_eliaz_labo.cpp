#include <iostream>
#include <string>
using namespace std;

class Empleado {
private:
    string nombre;
    double salario;

public:
    Empleado(string nom = "", double sal = 0.0) : nombre(nom), salario(sal) {}
    
    // Función miembro para ingresar datos
    void ingresarDatos() {
        cout << "Ingrese nombre del empleado: ";
        getline(cin, nombre);
        cout << "Ingrese salario: ";
        cin >> salario;
        cin.ignore(); // Limpiar buffer
    }
    
    // Función miembro que recibe un objeto Empleado y compara salarios
    string compararSalarios(const Empleado& otroEmpleado) const {
        if(salario > otroEmpleado.salario) {
            return nombre + " tiene mayor salario que " + otroEmpleado.nombre;
        } else if(salario < otroEmpleado.salario) {
            return otroEmpleado.nombre + " tiene mayor salario que " + nombre;
        } else {
            return nombre + " y " + otroEmpleado.nombre + " tienen el mismo salario";
        }
    }
    
    void mostrarDatos() const {
        cout << "Nombre: " << nombre << ", Salario: $" << salario << endl;
    }
    
    string getNombre() const { return nombre; }
    double getSalario() const { return salario; }
    
    void setNombre(const string& nom) { nombre = nom; }
    void setSalario(double sal) { salario = sal; }
};

int main() {
    Empleado empleado1, empleado2;
    
    cout << "=== DATOS DEL PRIMER EMPLEADO ===" << endl;
    empleado1.ingresarDatos();
    
    cout << "\n=== DATOS DEL SEGUNDO EMPLEADO ===" << endl;
    empleado2.ingresarDatos();
    
    cout << "\n=== INFORMACIÓN DE EMPLEADOS ===" << endl;
    cout << "Empleado 1 - ";
    empleado1.mostrarDatos();
    cout << "Empleado 2 - ";
    empleado2.mostrarDatos();
    
    cout << "\n=== COMPARACIÓN DE SALARIOS ===" << endl;
    cout << empleado1.compararSalarios(empleado2) << endl;
    
    return 0;
}
