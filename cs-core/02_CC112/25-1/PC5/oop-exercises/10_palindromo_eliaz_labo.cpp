#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

class Palindromo {
private:
    string cadena;
    
    // Función auxiliar para normalizar la cadena (quitar espacios y convertir a minúsculas)
    string normalizar(const string& str) {
        string normalizada = "";
        for(char c : str) {
            if(isalnum(c)) {
                normalizada += tolower(c);
            }
        }
        return normalizada;
    }

public:
    Palindromo(const string& str = "") : cadena(str) {}
    
    void setCadena(const string& str) {
        cadena = str;
    }
    
    string getCadena() const {
        return cadena;
    }
    
    // Método principal para verificar si una cadena es palíndromo
    bool esPalindromo() {
        string normalizada = normalizar(cadena);
        string invertida = normalizada;
        reverse(invertida.begin(), invertida.end());
        
        return normalizada == invertida;
    }
    
    // Método alternativo usando comparación manual
    bool esPalindromoManual() {
        string normalizada = normalizar(cadena);
        int longitud = normalizada.length();
        
        for(int i = 0; i < longitud / 2; i++) {
            if(normalizada[i] != normalizada[longitud - 1 - i]) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    string entrada;
    cout << "Ingrese una cadena para verificar si es palíndromo: ";
    getline(cin, entrada);
    
    Palindromo verificador(entrada);
    
    cout << "Cadena ingresada: \"" << entrada << "\"" << endl;
    
    if(verificador.esPalindromo()) {
        cout << "La cadena ES un palíndromo." << endl;
    } else {
        cout << "La cadena NO es un palíndromo." << endl;
    }
    
    // Ejemplos adicionales
    cout << "\nEjemplos de palíndromos:" << endl;
    string ejemplos[] = {"sos", "peep", "A man a plan a canal Panama", "racecar", "hello"};
    
    for(const string& ejemplo : ejemplos) {
        Palindromo test(ejemplo);
        cout << "\"" << ejemplo << "\" -> " << (test.esPalindromo() ? "SÍ" : "NO") << endl;
    }
    
    return 0;
}
