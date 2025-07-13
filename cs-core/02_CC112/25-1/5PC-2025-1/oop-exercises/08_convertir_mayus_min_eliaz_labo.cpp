#include <iostream>
#include <string>
#include <cctype>
using namespace std;

class ConvertirMayusMin {
private:
    string cadena;

public:
    ConvertirMayusMin(string str = "") : cadena(str) {}
    
    void setCadena(string str) {
        cadena = str;
    }
    
    string getCadena() const {
        return cadena;
    }
    
    // Convierte mayúsculas a minúsculas y viceversa
    string convertirCaso() {
        string resultado = cadena;
        for(char &c : resultado) {
            if(islower(c)) {
                c = toupper(c);
            } else if(isupper(c)) {
                c = tolower(c);
            }
        }
        return resultado;
    }
    
    // Convierte toda la cadena a mayúsculas
    string aMayusculas() {
        string resultado = cadena;
        for(char &c : resultado) {
            c = toupper(c);
        }
        return resultado;
    }
    
    // Convierte toda la cadena a minúsculas
    string aMinusculas() {
        string resultado = cadena;
        for(char &c : resultado) {
            c = tolower(c);
        }
        return resultado;
    }
};

int main() {
    string entrada;
    cout << "Ingrese una cadena de caracteres: ";
    getline(cin, entrada);
    
    ConvertirMayusMin conversor(entrada);
    
    cout << "\nOpciones:\n";
    cout << "1. Convertir mayús/min (intercambiar)\n";
    cout << "2. Todo a mayúsculas\n";
    cout << "3. Todo a minúsculas\n";
    cout << "Seleccione opción: ";
    
    int opcion;
    cin >> opcion;
    
    switch(opcion) {
        case 1:
            cout << "Resultado: " << conversor.convertirCaso() << endl;
            break;
        case 2:
            cout << "Resultado: " << conversor.aMayusculas() << endl;
            break;
        case 3:
            cout << "Resultado: " << conversor.aMinusculas() << endl;
            break;
        default:
            cout << "Opción inválida" << endl;
    }
    
    return 0;
}
