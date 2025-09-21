#include "sorting.cpp"
#include "array.cpp"
#include "utils.h"
#include <iostream>
using std::cout, std::endl;


int main() {
    int vec1[] = {7, 2, 5, 10};
    int vec2[] = {5, 2, 18, 1, 0, 14, 7, 3, 6};

    QuickSort(vec1, 4);
    QuickSort(vec2, 9);

    int resultado[13], tam_resultado;

    Merge(vec1, 4, vec2, 9, resultado, tam_resultado);
    PrintArray(vec1, 4);
    PrintArray(vec2, 9);
    cout << "Resultado: ";
    PrintArray(resultado, tam_resultado);
    return 0;
}

