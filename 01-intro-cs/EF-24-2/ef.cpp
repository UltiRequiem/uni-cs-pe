#include <iostream>
#include <string>

int main() {
    // ejemplos
    std::string registros[] = {
        "[2024-10-27 10:30:00] ERROR Conexión fallida al servidor.",
        "[2024-10-27 10:31:00] WARNING Disco casi lleno.",
        "[2024-10-27 10:32:00] INFO Sistema operativo iniciado correctamente.",
        "[2024-10-27 10:33:00] ERROR Error crítico en el módulo X.",
        "[2024-10-27 10:34:00] WARNING Posible fuga de memoria.",
        "[2024-10-27 10:35:00] INFO Proceso completado.",
        "[2024-10-27 10:36:00] UNKNOWN Mensaje desconocido."
    };

    int contadorError = 0;
    int contadorWarning = 0;
    int contadorInfo = 0;
    int contadorUnknown = 0;

    std::cout << "Mensajes de ERROR:\n";

    // revisar
    for (const auto& registro : registros) {
        if (registro.find("ERROR") != std::string::npos) {
            std::size_t pos = registro.find("ERROR") + 6;
            std::cout << " " << registro.substr(pos) << std::endl;
            contadorError++;

        } else if (registro.find("WARNING") != std::string::npos) {
            
            contadorWarning++;
        } else if (registro.find("INFO") != std::string::npos) {
            
            contadorInfo++;
        } else if (registro.find("UNKNOWN") != std::string::npos) {
            
            contadorUnknown++;
        }

    }

    std::cout << "Cantidad de mensajes por tipo:\n";
    std::cout << "ERROR: " << contadorError << std::endl;
    std::cout << "WARNING: " << contadorWarning << std::endl;
    std::cout << "INFO: " << contadorInfo << std::endl;
    std::cout << "UNKNOWN: " << contadorUnknown << std::endl;

    return 0;
}


#include <iostream>
using namespace std;

int sumaMaxima(int A[], int n, int S) {
    int maxSuma = 0;

    // 2^n iteraciones
    for (int i = 0; i < (1 << n); i++) {
        int sumaActual = 0;
        
        for (int j = 0; j < n; j++) {

            // si es que tienen algun bit en común
            // entonces sumar el valor de A[j]
            if (i & (1 << j)) {
                sumaActual += A[j];
            }
        }

        // actualiza la suma
        if (sumaActual <= S && sumaActual > maxSuma) {
            maxSuma = sumaActual;
        }
    }

    return maxSuma;
}

int main() {
    int A[] = {3, 34, 4, 12, 5, 2};
    int S;

    cout << "Ingrese el valor de S: ";
    cin >> S;

    int n = sizeof(A) / sizeof(A[0]);
    int resultado = sumaMaxima(A, n, S);

    cout << "La suma máxima que no supera a " << S << " es " << resultado << endl;

    return 0;
}


#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

int main() {
    // inicializamos lo random
    std::srand(std::time(0));

    int size = std::rand() % 11;
    std::vector<int> arr(size); // vector de tamanao al azar
    
    for (int i = 0; i < size; ++i) {
        arr[i] = std::rand() % 2; // 0 o 1
    }

    std::cout << "Arreglo generado (" << size << " elementos): ";

    // imprimimos el arreglo
    for (int num : arr) {
        std::cout << num << " ";
    }

    std::cout << std::endl;

    int x;

    std::cout << "Ingrese el valor de x: ";
    std::cin >> x;

    std::string poli;

    int result = 0;

    for (int i = 0; i < size; ++i) {
        if (arr[i] == 1) {
            if (!poli.empty()) {
                poli += " + ";
            }

            poli += "x^" + std::to_string(i);
            result += std::pow(x, i);
        }
    }

    std::cout << "Polinomio: " << poli << std::endl;
    std::cout << "Resultado al remplazar x por " << x << ": " << result << std::endl;

    return 0;
}


#include <iostream>

int sumaRecursiva(int arr[], int indice, int tamaño) {
    // aqui la suma siempre es 0
    if (indice == tamaño) {
        return 0;
    }
    return arr[indice] + sumaRecursiva(arr, indice + 1, tamaño);
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int tamaño = sizeof(arr) / sizeof(arr[0]);
    int indice = 2; 

    int resultado = sumaRecursiva(arr, indice, tamaño);
    
    std::cout << "La suma desde el índice " << indice << " es: " << resultado << std::endl;

    return 0;
}
