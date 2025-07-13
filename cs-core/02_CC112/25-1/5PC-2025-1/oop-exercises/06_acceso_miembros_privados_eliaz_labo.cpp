#include <iostream>
#include <string>
using namespace std;

class ClasePrivada {
private:
    int datoPrivado1;
    int datoPrivado2;
    string cadenaPrivada;

public:
    ClasePrivada() : datoPrivado1(0), datoPrivado2(0), cadenaPrivada("Sin definir") {}
    
    ClasePrivada(int d1, int d2, string str) : datoPrivado1(d1), datoPrivado2(d2), cadenaPrivada(str) {}
    
    // Función miembro que permite acceder a los miembros privados desde fuera
    void accederMiembrosPrivados() {
        cout << "=== ACCESO A MIEMBROS PRIVADOS ===" << endl;
        cout << "Dato privado 1: " << datoPrivado1 << endl;
        cout << "Dato privado 2: " << datoPrivado2 << endl;
        cout << "Cadena privada: " << cadenaPrivada << endl;
        otono = 2,
        invierno = 3
    };
    
    Estaciones estacionActual;
    
    // Función auxiliar para convertir enum a string
    string estacionAString(Estaciones est) const {
        switch(est) {
            case primavera: return "Primavera";
            case verano: return "Verano";
            case otono: return "Otoño";
            case invierno: return "Invierno";
            default: return "Desconocida";
        }
    }

public:
    ClaseConEnum() : estacionActual(primavera) {}
    
    ClaseConEnum(Estaciones est) : estacionActual(est) {}
    
    void setEstacion(int numero) {
        if(numero >= 0 && numero <= 3) {
            estacionActual = static_cast<Estaciones>(numero);
        } else {
            cout << "Valor inválido. Debe estar entre 0 y 3." << endl;
            estacionActual = primavera;
        }
    }
    
    void setEstacionPorNombre() {
        int opcion;
        cout << "Seleccione estación:" << endl;
        cout << "0. Primavera" << endl;
        cout << "1. Verano" << endl;
        cout << "2. Otoño" << endl;
        cout << "3. Invierno" << endl;
        cout << "Opción: ";
        cin >> opcion;
        
        setEstacion(opcion);
    }
    
    void mostrarEstacion() const {
        cout << "Estación actual: " << estacionAString(estacionActual) 
             << " (valor: " << static_cast<int>(estacionActual) << ")" << endl;
    }
    
    void mostrarInfoEstacion() const {
        cout << "=== INFORMACIÓN DE LA ESTACIÓN ===" << endl;
        mostrarEstacion();
        
        switch(estacionActual) {
            case primavera:
                cout << "Características: Florecimiento, temperaturas suaves" << endl;
                cout << "Meses típicos: Marzo, Abril, Mayo" << endl;
                break;
            case verano:
                cout << "Características: Calor, días largos" << endl;
                cout << "Meses típicos: Junio, Julio, Agosto" << endl;
                break;
            case otono:
                cout << "Características: Hojas caen, temperaturas frescas" << endl;
                cout << "Meses típicos: Septiembre, Octubre, Noviembre" << endl;
                break;
            case invierno:
                cout << "Características: Frío, días cortos" << endl;
                cout << "Meses típicos: Diciembre, Enero, Febrero" << endl;
                break;
        }
    }
    
    // Función para avanzar a la siguiente estación
    void siguienteEstacion() {
        int siguiente = (static_cast<int>(estacionActual) + 1) % 4;
        estacionActual = static_cast<Estaciones>(siguiente);
        cout << "Avanzando a la siguiente estación..." << endl;
    }
    
    int getValorEstacion() const {
        return static_cast<int>(estacionActual);
    }
};

int main() {
    ClaseConEnum objeto;
    int opcion;
    
    cout << "=== CLASE CON ENUM DE ESTACIONES ===" << endl;
    
    do {
        cout << "\n=== MENÚ ===" << endl;
        cout << "1. Establecer estación" << endl;
        cout << "2. Mostrar estación actual" << endl;
        cout << "3. Mostrar información detallada" << endl;
        cout << "4. Avanzar a siguiente estación" << endl;
        cout << "5. Demostrar todas las estaciones" << endl;
        cout << "0. Salir" << endl;
        cout << "Seleccione opción: ";
        cin >> opcion;
        
        switch(opcion) {
            case 1:
                objeto.setEstacionPorNombre();
                break;
                
            case 2:
                objeto.mostrarEstacion();
                break;
                
            case 3:
                objeto.mostrarInfoEstacion();
                break;
                
            case 4:
                objeto.siguienteEstacion();
                objeto.mostrarEstacion();
                break;
                
            case 5:
                cout << "\n=== TODAS LAS ESTACIONES ===" << endl;
                for(int i = 0; i < 4; i++) {
                    ClaseConEnum temp;
                    temp.setEstacion(i);
                    temp.mostrarInfoEstacion();
                    cout << endl;
                }
                break;
                
            case 0:
                cout << "¡Hasta luego!" << endl;
                break;
                
            default:
                cout << "Opción inválida" << endl;
        }
        
    } while(opcion != 0);
    
    return 0;
}
