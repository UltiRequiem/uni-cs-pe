#include <iostream>
using namespace std;

class Punto {
private:
    double x, y;

public:
    Punto(double coordX = 0.0, double coordY = 0.0) : x(coordX), y(coordY) {}
    
    void setCoordenadas(double coordX, double coordY) {
        x = coordX;
        y = coordY;
    }
    
    double getX() const { return x; }
    double getY() const { return y; }
    
    void mostrarPunto() const {
        cout << "(" << x << ", " << y << ")";
    }
    
    void ingresarCoordenadas(int numeroPunto) {
        cout << "Punto " << numeroPunto << " - Ingrese coordenada X: ";
        cin >> x;
        cout << "Punto " << numeroPunto << " - Ingrese coordenada Y: ";
        cin >> y;
    }
};

int main() {
    const int NUM_PUNTOS = 10;
    Punto puntos[NUM_PUNTOS];  // Arreglo de objetos
    
    cout << "=== INGRESO DE COORDENADAS ===" << endl;
    for(int i = 0; i < NUM_PUNTOS; i++) {
        puntos[i].ingresarCoordenadas(i + 1);
        cout << endl;
    }
    
    cout << "=== COORDENADAS DE LOS 10 PUNTOS ===" << endl;
    for(int i = 0; i < NUM_PUNTOS; i++) {
        cout << "Punto " << (i + 1) << ": ";
        puntos[i].mostrarPunto();
        cout << endl;
    }
    
    // Ejemplo adicional con puntos predefinidos
    cout << "\n=== EJEMPLO CON PUNTOS PREDEFINIDOS ===" << endl;
    Punto ejemplos[5] = {
        Punto(1.5, 2.3),
        Punto(-3.7, 4.1),
        Punto(0.0, -2.8),
        Punto(5.2, 1.9),
        Punto(-1.1, -3.4)
    };
    
    for(int i = 0; i < 5; i++) {
        cout << "Ejemplo " << (i + 1) << ": ";
        ejemplos[i].mostrarPunto();
        cout << endl;
    }
    
    return 0;
}
