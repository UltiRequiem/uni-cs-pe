#include <iostream>
using namespace std;

class ClaseEnum {
private:
    // Definición del enum dentro de la clase
    enum Estaciones {primavera, verano, otono, invierno};
    Estaciones estacionActual;
    
    // Enum adicional con valores personalizados
    enum Colores {rojo = 10, verde = 20, azul = 30, amarillo = 40};
    Colores colorFavorito;

public:
    ClaseEnum() : estacionActual(primavera), colorFavorito(rojo) {}
    
    void setEstacion(int opcion) {
        switch(opcion) {
            case 0: estacionActual = primavera; break;
            case 1: estacionActual = verano; break;
            case 2: estacionActual = otono; break;
            case 3: estacionActual = invierno; break;
            default: 
                cout << "Opción inválida. Se mantiene estación actual." << endl;
        }
    }
    
    void setColor(int opcion) {
        switch(opcion) {
            case 1: colorFavorito = rojo; break;
            case 2: colorFavorito = verde; break;
            case 3: colorFavorito = azul; break;
            case 4: colorFavorito = amarillo; break;
            default:
                cout << "Opción inválida. Se mantiene color actual." << endl;
        }
    }
    
    void mostrarEstacion() const {
        cout << "Estación actual: ";
        switch(estacionActual) {
            case primavera: cout << "Primavera (valor: " << primavera << ")"; break;
            case verano: cout << "Verano (valor: " << verano << ")"; break;
            case otono: cout << "Otoño (valor: " << otono << ")"; break;
            case invierno: cout << "Invierno (valor: " << invierno << ")"; break;
        }
        cout << endl;
    }
    
    void mostrarColor() const {
        cout << "Color favorito: ";
        switch(colorFavorito) {
            case rojo: cout << "Rojo (valor: " << rojo << ")"; break;
            case verde: cout << "Verde (valor: " << verde << ")"; break;
            case azul: cout << "Azul (valor: " << azul << ")"; break;
            case amarillo: cout << "Amarillo (valor: " << amarillo << ")"; break;
        }
        cout << endl;
    }
};

int main() {
    ClaseEnum objeto;
    int opcion;
    
    cout << "=== CLASE CON TIPO ENUM ===" << endl;
    
    // Mostrar valores por defecto
    cout << "\nValores por defecto:" << endl;
    objeto.mostrarEstacion();
    objeto.mostrarColor();
    
    // Seleccionar estación
    cout << "\n=== SELECCIONAR ESTACIÓN ===" << endl;
    cout << "0. Primavera\n1. Verano\n2. Otoño\n3. Invierno" << endl;
    cout << "Seleccione una estación: ";
    cin >> opcion;
    objeto.setEstacion(opcion);
    
    // Seleccionar color
    cout << "\n=== SELECCIONAR COLOR ===" << endl;
    cout << "1. Rojo\n2. Verde\n3. Azul\n4. Amarillo" << endl;
    cout << "Seleccione un color: ";
    cin >> opcion;
    objeto.setColor(opcion);
    
    // Mostrar selecciones
    cout << "\n=== SELECCIONES FINALES ===" << endl;
    objeto.mostrarEstacion();
    objeto.mostrarColor();
    
    return 0;
}
