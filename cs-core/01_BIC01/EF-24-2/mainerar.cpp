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
