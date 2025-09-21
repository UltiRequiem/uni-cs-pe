#include <iostream>
using namespace std;

class Time {
private:
    int horas;
    int minutos;
    int segundos;
    
    // Función auxiliar para normalizar el tiempo cuando excede límites
    void normalizar() {
        if(segundos >= 60) {
            minutos += segundos / 60;
            segundos %= 60;
        }
        if(minutos >= 60) {
            horas += minutos / 60;
            minutos %= 60;
        }
        // Mantener formato de 24 horas
        horas %= 24;
    }

public:
    Time(int hh = 0, int mm = 0, int ss = 0) : horas(hh), minutos(mm), segundos(ss) {
        normalizar();
    }
    
    // Función miembro para sumar dos tiempos
    Time sum_time(const Time& tiempo1, const Time& tiempo2) {
        int totalHoras = tiempo1.horas + tiempo2.horas;
        int totalMinutos = tiempo1.minutos + tiempo2.minutos;
        int totalSegundos = tiempo1.segundos + tiempo2.segundos;
        
        Time resultado(totalHoras, totalMinutos, totalSegundos);
        return resultado;
    }
    
    void mostrarTiempo() const {
        printf("%02d:%02d:%02d\n", horas, minutos, segundos);
    }
    
    void ingresarTiempo() {
        cout << "Ingrese horas: ";
        cin >> horas;
        cout << "Ingrese minutos: ";
        cin >> minutos;
        cout << "Ingrese segundos: ";
        cin >> segundos;
        normalizar();
    }
    
    // Getters
    int getHoras() const { return horas; }
    int getMinutos() const { return minutos; }
    int getSegundos() const { return segundos; }
};

int main() {
    Time tiempo1, tiempo2, resultado;
    
    cout << "=== PRIMER TIEMPO ===" << endl;
    tiempo1.ingresarTiempo();
    
    cout << "\n=== SEGUNDO TIEMPO ===" << endl;
    tiempo2.ingresarTiempo();
    
    cout << "\n=== RESULTADOS ===" << endl;
    cout << "Tiempo 1: ";
    tiempo1.mostrarTiempo();
    cout << "Tiempo 2: ";
    tiempo2.mostrarTiempo();
    
    // Usando la función sum_time para calcular la suma
    resultado = resultado.sum_time(tiempo1, tiempo2);
    cout << "Suma:     ";
    resultado.mostrarTiempo();
    
    cout << "\n=== EJEMPLO DEL ENUNCIADO ===" << endl;
    Time ejemplo1(3, 35, 45);
    Time ejemplo2(4, 56, 45);
    Time ejemploResultado;
    
    cout << "Tiempo1 = ";
    ejemplo1.mostrarTiempo();
    cout << "Tiempo2 = ";
    ejemplo2.mostrarTiempo();
    
    ejemploResultado = ejemploResultado.sum_time(ejemplo1, ejemplo2);
    cout << "Resultado: ";
    ejemploResultado.mostrarTiempo();
    
    return 0;
}
