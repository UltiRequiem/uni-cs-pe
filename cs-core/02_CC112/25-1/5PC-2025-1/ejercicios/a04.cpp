#include <iostream>

class VectorDinamico
{
    int *datos;

    int capacidad, tam;

    void redimensionar()
    {
        int nuevaCap = capacidad * 2;
        int *nuevo = new int[nuevaCap];
        for (int i = 0; i < tam; ++i)
            nuevo[i] = datos[i];
        delete[] datos;
        datos = nuevo;
        capacidad = nuevaCap;
    }

public:
    VectorDinamico() : capacidad(2), tam(0)
    {
        datos = new int[capacidad];
    }

    ~VectorDinamico() { delete[] datos; }

    void agregar(int valor)
    {
        if (tam == capacidad)
            redimensionar();
        datos[tam++] = valor;
    }

    void mostrar() const
    {
        for (int i = 0; i < tam; ++i)
            std::cout << datos[i] << " ";
        std::cout << std::endl;
    }
};

int main()
{
    VectorDinamico v;

    v.agregar(1);
    v.agregar(2);
    v.agregar(3);
    v.mostrar();

    return 0;
}
