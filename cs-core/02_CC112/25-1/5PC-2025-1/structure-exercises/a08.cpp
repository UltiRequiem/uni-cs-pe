#include <iostream>

struct Nodo
{
    int fila, col, valor;
    Nodo *sig;
    Nodo(int f, int c, int v) : fila(f), col(c), valor(v), sig(nullptr) {}
};

class MatrizDispersa
{
    Nodo *cabeza;

public:
    MatrizDispersa() : cabeza(nullptr) {}

    ~MatrizDispersa()
    {
        while (cabeza)
        {
            Nodo *temp = cabeza;
            cabeza = cabeza->sig;
            delete temp;
        }
    }

    void insertar(int f, int c, int v)
    {
        if (v == 0)
            return;
        Nodo *nuevo = new Nodo(f, c, v);
        nuevo->sig = cabeza;
        cabeza = nuevo;
    }

    int buscar(int f, int c)
    {
        Nodo *temp = cabeza;
        while (temp)
        {
            if (temp->fila == f && temp->col == c)
                return temp->valor;
            temp = temp->sig;
        }
        return 0;
    }

    void imprimir(int filas, int cols)
    {
        for (int i = 0; i < filas; ++i)
        {
            for (int j = 0; j < cols; ++j)
                std::cout << buscar(i, j) << " ";
            std::cout << std::endl;
        }
    }
};

int main()
{
    MatrizDispersa m;

    m.insertar(0, 1, 5);
    m.insertar(2, 0, 8);
    m.imprimir(3, 3);

    return 0;
}
