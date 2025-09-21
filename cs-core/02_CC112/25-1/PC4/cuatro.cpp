#include <iostream>
#include <string>
#include <fstream>

using std::string;
using std::endl;
using std::cout;
using std::cin;
using std::ofstream;
using std::ifstream;
using std::ios;

class Alumno {
    public:
    string codigo;
    string nombre;
    float nota;
};

int main(){
    int n;
    cout << "Ingrese la cantidad de alumnos: ";
    cin >> n;

    Alumno *alumnos = new Alumno[n];

    for (int i = 0; i < n; i++) {
        cout << "Ingrese el codigo del alumno " << i + 1 << ": ";
        cin >> alumnos[i].codigo;
         cout << "Ingrese el nombre del alumno " << i + 1 << ": ";
        cin >> alumnos[i].nombre;
        cout << "Ingrese la nota del alumno " << i + 1 << ": ";
        cin >> alumnos[i].nota;
    }

    ofstream outFile("alumnos.dat", ios::binary);

    if (outFile.is_open()) {
        outFile.write(reinterpret_cast<char*>(alumnos), n * sizeof(Alumno));
        outFile.close();
    } else {
        cout << "Error al abrir el archivo para escribir." << endl;
        return 1; // ahi no mas
    }

    // ordenar los alumnos por nota directamente en el archivo
    ifstream inFile("alumnos.dat", ios::binary);
    
    if (!inFile.is_open()) {
        cout << "Error al abrir el archivo para leer." << endl;
        return 1; 
    }
    
    Alumno *alumnosRead = new Alumno[n];
    
    inFile.read(reinterpret_cast<char*>(alumnosRead), n * sizeof(Alumno));
    inFile.close();
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (alumnosRead[j].nota > alumnosRead[j + 1].nota) {
                Alumno temp = alumnosRead[j];
                alumnosRead[j] = alumnosRead[j + 1];
                alumnosRead[j + 1] = temp;
            }
        }
    }

    cout << endl;
    cout << "Registros ordenados por nota (descendente):" << endl;
    cout << endl;

    for (int i = n - 1; i >= 0; i--) {
        cout << "Codigo: " << alumnosRead[i].codigo 
             << "- Nombre: " << alumnosRead[i].nombre 
             << ", Nota: " << alumnosRead[i].nota << endl;
    }
    
    delete[] alumnos;
    delete[] alumnosRead;

    return 0;
}