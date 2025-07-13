#include <iostream>
#include <string>
using namespace std;

class Estudiante {
private:
    string nombre;
    int edad;
    int ciclo;

public:
    Estudiante() : nombre(""), edad(0), ciclo(1) {}
    
    Estudiante(string nom, int ed, int cic) : nombre(nom), edad(ed), ciclo(cic) {}
    
    // Función miembro para ingresar datos
    void ingresarDatos() {
        cout << "Ingrese nombre del estudiante: ";
        getline(cin, nombre);
        cout << "Ingrese edad: ";
        cin >> edad;
        cout << "Ingrese ciclo: ";
        cin >> ciclo;
        cin.ignore(); // Limpiar buffer
    }
    
    // Función miembro para mostrar datos
    void mostrarDatos() const {
        cout << "Nombre: " << nombre << endl;
        cout << "Edad: " << edad << " años" << endl;
        cout << "Ciclo: " << ciclo << endl;
    }
    
    // Getters adicionales
    string getNombre() const { return nombre; }
    int getEdad() const { return edad; }
    int getCiclo() const { return ciclo; }
};

int main() {
    Estudiante estudiante1, estudiante2;
    
    cout << "=== INGRESO DE DATOS DEL PRIMER ESTUDIANTE ===" << endl;
    estudiante1.ingresarDatos();
    
    cout << "\n=== INGRESO DE DATOS DEL SEGUNDO ESTUDIANTE ===" << endl;
    estudiante2.ingresarDatos();
    
    cout << "\n=== INFORMACIÓN DEL PRIMER ESTUDIANTE ===" << endl;
    estudiante1.mostrarDatos();
    
    cout << "\n=== INFORMACIÓN DEL SEGUNDO ESTUDIANTE ===" << endl;
    estudiante2.mostrarDatos();
    
    // Comparación adicional
    cout << "\n=== COMPARACIÓN ===" << endl;
    if(estudiante1.getEdad() > estudiante2.getEdad()) {
        cout << estudiante1.getNombre() << " es mayor que " << estudiante2.getNombre() << endl;
    } else if(estudiante1.getEdad() < estudiante2.getEdad()) {
        cout << estudiante2.getNombre() << " es mayor que " << estudiante1.getNombre() << endl;
    } else {
        cout << "Ambos estudiantes tienen la misma edad." << endl;
    }
    
    return 0;
}
