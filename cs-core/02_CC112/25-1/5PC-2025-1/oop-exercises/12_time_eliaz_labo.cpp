#include <iostream>
using namespace std;

class Time {
private:
    int horas;
    int minutos;
    int segundos;
    
    // Función auxiliar para validar tiempo
    bool esValido(int hh, int mm, int ss) {
        return (hh >= 0 && hh < 24) && (mm >= 0 && mm < 60) && (ss >= 0 && ss < 60);
    }

public:
    Time(int hh = 0, int mm = 0, int ss = 0) {
        if(esValido(hh, mm, ss)) {
            horas = hh;
            minutos = mm;
            segundos = ss;
        } else {
            horas = minutos = segundos = 0;
        }
    }
    
    // Función miembro para ingresar datos
    void input_time(int hh, int mm, int ss) {
        if(esValido(hh, mm, ss)) {
            horas = hh;
            minutos = mm;
            segundos = ss;
        } else {
            cout << "Tiempo inválido. Se estableció a 00:00:00" << endl;
            horas = minutos = segundos = 0;
        }
    }
    
    // Función miembro para comparar dos objetos de tiempo
    string comp_time(const Time& otroTiempo) const {
        int totalSegundos1 = horas * 3600 + minutos * 60 + segundos;
        int totalSegundos2 = otroTiempo.horas * 3600 + otroTiempo.minutos * 60 + otroTiempo.segundos;
        
        if(totalSegundos1 > totalSegundos2) {
            return "El primer tiempo es mayor";
        } else if(totalSegundos1 < totalSegundos2) {
            return "El segundo tiempo es mayor";
        } else {
            return "Los tiempos son iguales";
        }
    }
    
    void mostrarTiempo() const {
        printf("%02d:%02d:%02d\n", horas, minutos, segundos);
    }
    
    // Getters
    int getHoras() const { return horas; }
    int getMinutos() const { return minutos; }
    int getSegundos() const { return segundos; }
};

int main() {
    int h1, m1, s1, h2, m2, s2;
    
    cout << "=== PRIMER TIEMPO ===" << endl;
    cout << "Ingrese horas (0-23): ";
    cin >> h1;
    cout << "Ingrese minutos (0-59): ";
    cin >> m1;
    cout << "Ingrese segundos (0-59): ";
    cin >> s1;
    
    Time tiempo1;
    tiempo1.input_time(h1, m1, s1);
    
    cout << "\n=== SEGUNDO TIEMPO ===" << endl;
    cout << "Ingrese horas (0-23): ";
    cin >> h2;
    cout << "Ingrese minutos (0-59): ";
    cin >> m2;
    cout << "Ingrese segundos (0-59): ";
    cin >> s2;
    
    Time tiempo2;
    tiempo2.input_time(h2, m2, s2);
    
    cout << "\n=== RESULTADOS ===" << endl;
    cout << "Primer tiempo: ";
    tiempo1.mostrarTiempo();
    cout << "Segundo tiempo: ";
    tiempo2.mostrarTiempo();
    
    cout << "\nComparación: " << tiempo1.comp_time(tiempo2) << endl;
    
    return 0;
}
