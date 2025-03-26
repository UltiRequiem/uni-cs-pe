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
