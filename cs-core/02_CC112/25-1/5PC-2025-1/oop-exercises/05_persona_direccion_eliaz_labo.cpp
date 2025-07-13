#include <iostream>
#include <string>
using namespace std;

class Persona {
private:
    string nombre;
    int edad;
    double salario;
    
    // Estructura anidada para la dirección
    struct Direccion {
        int hno;        // número de casa
        string calle;
        string ciudad;
        string estado;
        
        // Constructor por defecto para la estructura
        Direccion() : hno(0), calle(""), ciudad(""), estado("") {}
    };
    
    Direccion direccion;

public:
    Persona() : nombre(""), edad(0), salario(0.0) {}
    
    // Función miembro para ingresar datos
    void ingresarDatos() {
        cout << "=== DATOS PERSONALES ===" << endl;
        cout << "Ingrese nombre: ";
        getline(cin, nombre);
        
        cout << "Ingrese edad: ";
        cin >> edad;
        
        cout << "Ingrese salario: ";
        cin >> salario;
        
        cout << "\n=== DIRECCIÓN ===" << endl;
        cout << "Ingrese número de casa: ";
        cin >> direccion.hno;
        cin.ignore(); // Limpiar buffer
        
        cout << "Ingrese calle: ";
        getline(cin, direccion.calle);
        
        cout << "Ingrese ciudad: ";
        getline(cin, direccion.ciudad);
        
        cout << "Ingrese estado: ";
        getline(cin, direccion.estado);
    }
    
    // Función miembro para mostrar datos
    void mostrarDatos() const {
        cout << "=== INFORMACIÓN PERSONAL ===" << endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Edad: " << edad << " años" << endl;
        cout << "Salario: $" << salario << endl;
        
        cout << "\n=== DIRECCIÓN ===" << endl;
        cout << "Número de casa: " << direccion.hno << endl;
        cout << "Calle: " << direccion.calle << endl;
        cout << "Ciudad: " << direccion.ciudad << endl;
        cout << "Estado: " << direccion.estado << endl;
        
        cout << "\nDirección completa: " << direccion.hno << " " 
             << direccion.calle << ", " << direccion.ciudad 
             << ", " << direccion.estado << endl;
    }
    
    // Getters para acceso controlado
    string getNombre() const { return nombre; }
    int getEdad() const { return edad; }
    double getSalario() const { return salario; }
    string getDireccionCompleta() const {
        return to_string(direccion.hno) + " " + direccion.calle + 
               ", " + direccion.ciudad + ", " + direccion.estado;
    }
    
    // Función para comparar salarios con otra persona
    void compararSalario(const Persona& otra) const {
        cout << "\n=== COMPARACIÓN DE SALARIOS ===" << endl;
        if(salario > otra.salario) {
            cout << nombre << " gana más que " << otra.nombre << endl;
        } else if(salario < otra.salario) {
            cout << otra.nombre << " gana más que " << nombre << endl;
        } else {
            cout << nombre << " y " << otra.nombre << " ganan lo mismo" << endl;
        }
        
        cout << "Diferencia: $" << abs(salario - otra.salario) << endl;
    }
};

int main() {
    int numPersonas;
    cout << "¿Cuántas personas desea registrar? ";
    cin >> numPersonas;
    cin.ignore(); // Limpiar buffer
    
    Persona* personas = new Persona[numPersonas];
    
    // Ingresar datos de todas las personas
    for(int i = 0; i < numPersonas; i++) {
        cout << "\n=== PERSONA " << (i + 1) << " ===" << endl;
        personas[i].ingresarDatos();
    }
    
    // Mostrar datos de todas las personas
    cout << "\n" << string(50, '=') << endl;
    cout << "INFORMACIÓN DE TODAS LAS PERSONAS REGISTRADAS" << endl;
    cout << string(50, '=') << endl;
    
    for(int i = 0; i < numPersonas; i++) {
        cout << "\n--- PERSONA " << (i + 1) << " ---" << endl;
        personas[i].mostrarDatos();
    }
    
    // Comparar salarios si hay más de una persona
    if(numPersonas >= 2) {
        cout << "\n" << string(40, '=') << endl;
        cout << "COMPARACIONES DE SALARIO" << endl;
        cout << string(40, '=') << endl;
        
        for(int i = 0; i < numPersonas - 1; i++) {
            personas[i].compararSalario(personas[i + 1]);
        }
    }
    
    delete[] personas; // Liberar memoria dinámica
    return 0;
}
