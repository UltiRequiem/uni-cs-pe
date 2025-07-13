#include <iostream>

class VectorEnteros
{
    int *arreglo;
    int tam;

public:
    VectorEnteros(int n) : tam(n)
    {
        arreglo = new int[tam];
    }

    ~VectorEnteros() { delete[] arreglo; }

    void llenar()
    {
        for (int i = 0; i < tam; ++i)
        {
            std::cout << "Valor " << i << ": ";
            std::cin >> arreglo[i];
        }
    }

    void mostrar() const
    {
        for (int i = 0; i < tam; ++i)
        {
            std::cout << arreglo[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main()
{
    int n;
    std::cout << "Tamaño: ";
    std::cin >> n;

    VectorEnteros v(n);

    v.llenar();
    v.mostrar();

    return 0;
}
