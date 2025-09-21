#include <iostream>
#include <string>
#include <cstring>
using namespace std;

class InvertirCadena {
private:
    char* cadena;
    int longitud;

public:
    // Constructor que usa asignación dinámica de memoria
    InvertirCadena(const string& str) {
        longitud = str.length();
        cadena = new char[longitud + 1];
        strcpy(cadena, str.c_str());
    }
    
    // Destructor para liberar memoria dinámica
    ~InvertirCadena() {
        delete[] cadena;
    }
    
    // Constructor de copia para manejo correcto de memoria dinámica
    InvertirCadena(const InvertirCadena& otra) {
        longitud = otra.longitud;
        cadena = new char[longitud + 1];
        strcpy(cadena, otra.cadena);
    }
    
    // Función miembro que invierte la cadena usando memoria dinámica
    void invertir() {
        char* temp = new char[longitud + 1];
        
        for(int i = 0; i < longitud; i++) {
            temp[i] = cadena[longitud - 1 - i];
        }
        temp[longitud] = '\0';
        
        // Copiar el resultado invertido de vuelta a la cadena original
        strcpy(cadena, temp);
        delete[] temp;
    }
    
    void mostrarCadena() const {
        cout << cadena << endl;
    }
    
    string obtenerCadena() const {
        return string(cadena);
    }
};

int main() {
    string entrada;
    cout << "Ingrese una cadena de caracteres: ";
    getline(cin, entrada);
    
    InvertirCadena inversor(entrada);
    
    cout << "Cadena original: ";
    inversor.mostrarCadena();
    
    inversor.invertir();
    
    cout << "Cadena invertida: ";
    inversor.mostrarCadena();
    
    return 0;
}
