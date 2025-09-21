#include <iostream>
#include <string>
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::ios;

class Sismo{
    public:
    int id;
    string fecha;
    string hora;
    float magnitud;
    string ubicacion;
};

void displayarOpciones(){
    cout << "Opciones:" << endl;
    cout << "1. Mostrar sismos" << endl;
    cout << "2. Registrar sismo" << endl;
    cout << "3. Salir" << endl;
}

int main(){
    displayarOpciones();
    int opcion;
    cout << "Ingrese una opcion: ";
    cin >> opcion;


    if (opcion == 1) {
        ifstream inFile("sismos.txt");

        if (!inFile) {
            cout << "Error al abrir el archivo." << endl;
            return 1;
        }

        Sismo sismo;
        
        while (inFile >> sismo.id >> sismo.fecha >> sismo.hora >> sismo.magnitud >> sismo.ubicacion) {
            cout << "ID: " << sismo.id << ", Fecha: " << sismo.fecha 
                 << ", Hora: " << sismo.hora << ", Magnitud: " << sismo.magnitud 
                 << ", Ubicacion: " << sismo.ubicacion << endl;
        }
        inFile.close();

    } else if (opcion == 2) {
        ofstream outFile("sismos.txt", ios::app);

        if (!outFile) {
            cout << "Error al abrir el archivo." << endl;
            cout << "Puede que sea la primera vez que se ejecuta el programa." << endl;
            return 1;
        }

        Sismo nuevoSismo;
        
        cout << "Ingrese ID del sismo: ";
        cin >> nuevoSismo.id;
        cout << "Ingrese fecha (DD/MM/AAAA): ";
        cin >> nuevoSismo.fecha;
        cout << "Ingrese hora (HH:MM): ";
        cin >> nuevoSismo.hora;
        cout << "Ingrese magnitud: ";
        cin >> nuevoSismo.magnitud;
        cout << "Ingrese ubicacion: ";
        cin.ignore();

        getline(cin, nuevoSismo.ubicacion);

        outFile << nuevoSismo.id << " " << nuevoSismo.fecha << " "
                << nuevoSismo.hora << " " << nuevoSismo.magnitud 
                << " " << nuevoSismo.ubicacion << endl;

        outFile.close();
    } else if (opcion == 3) {
        cout << "Saliendo del programa." << endl;
    } else {
        cout << "Opcion no valida." << endl;
    }

    return 0;
}