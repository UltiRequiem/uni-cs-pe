#include <iostream>
#include <vector>
using namespace std;

class Matriz {
private:
    int n; // orden de la matriz cuadrada
    vector<vector<int>> matriz;

public:
    Matriz(int orden) : n(orden) {
        matriz.resize(n, vector<int>(n));
    }
    
    void llenarMatriz() {
        cout << "Ingrese elementos de la matriz " << n << "x" << n << ":\n";
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                cout << "Elemento [" << i << "][" << j << "]: ";
                cin >> matriz[i][j];
            }
        }
    }
    
    // Método para ordenar los elementos por filas usando bubble sort
    void ordenarPorFilas() {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n - 1; j++) {
                for(int k = 0; k < n - j - 1; k++) {
                    if(matriz[i][k] > matriz[i][k+1]) {
                        swap(matriz[i][k], matriz[i][k+1]);
                    }
                }
            }
        }
    }
    
    // Método para calcular suma de diagonal principal
    void sumarDiagonalPrincipal() {
        int suma = 0;
        cout << "Elementos de la diagonal principal: ";
        for(int i = 0; i < n; i++) {
            cout << matriz[i][i];
            if(i < n-1) cout << " + ";
            suma += matriz[i][i];
        }
        cout << " = " << suma << endl;
    }
    
    void mostrarMatriz() {
        cout << "Matriz:\n";
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                cout << matriz[i][j] << "\t";
            }
            cout << endl;
        }
    }
};

int main() {
    int orden;
    cout << "=== MATRIZ CUADRADA ===" << endl;
    cout << "Ingrese el orden de la matriz cuadrada: ";
    cin >> orden;
    
    if(orden <= 0) {
        cout << "Error: El orden debe ser positivo." << endl;
        return 1;
    }
    
    Matriz mat(orden);
    mat.llenarMatriz();
    
    cout << "\n=== MATRIZ ORIGINAL ===" << endl;
    mat.mostrarMatriz();
    
    cout << "\n=== SUMA DE DIAGONAL PRINCIPAL ===" << endl;
    mat.sumarDiagonalPrincipal();
    
    cout << "\n=== ORDENANDO ELEMENTOS POR FILAS ===" << endl;
    mat.ordenarPorFilas();
    
    cout << "\n=== MATRIZ CON FILAS ORDENADAS ===" << endl;
    mat.mostrarMatriz();
    
    cout << "\n=== NUEVA SUMA DE DIAGONAL PRINCIPAL ===" << endl;
    mat.sumarDiagonalPrincipal();
    
    return 0;
}
