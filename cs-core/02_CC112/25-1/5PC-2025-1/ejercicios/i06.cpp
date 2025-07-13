#include <iostream>

using std::min;

int *redimensionar(int *arr, int oldSize, int newSize)
{
    int *nuevo = new int[newSize];

    int maxSize = min(oldSize, newSize);

    for (int i = 0; i < maxSize; ++i)
    {
        nuevo[i] = arr[i];
    }

    delete[] arr;
    return nuevo;
}

int main()
{
    int n;
    std::cout << "Tamaño inicial: ";
    std::cin >> n;

    int *arr = new int[n];

    for (int i = 0; i < n; ++i)
    {
        std::cout << "Valor " << i << ": ";
        std::cin >> arr[i];
    }

    int nuevoTam;
    std::cout << "Nuevo tamaño: ";
    std::cin >> nuevoTam;

    arr = redimensionar(arr, n, nuevoTam);

    std::cout << "Arreglo redimensionado:\n";

    for (int i = 0; i < nuevoTam; ++i)
    {
        std::cout << arr[i] << " ";
    }

    std::cout << std::endl;

    delete[] arr;

    return 0;
}
