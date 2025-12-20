#include <iostream>

struct Nodo
{
    int dato;
    Nodo *izq;
    Nodo *der;
    Nodo(int d) : dato(d), izq(nullptr), der(nullptr) {}
};

class ArbolBinario
{
    Nodo *raiz;
    void insertar(Nodo *&nodo, int valor)
    {
        if (!nodo)
            nodo = new Nodo(valor);
        else if (valor < nodo->dato)
            insertar(nodo->izq, valor);
        else
            insertar(nodo->der, valor);
    }

    void inorden(Nodo *nodo)
    {
        if (!nodo)
            return;
        inorden(nodo->izq);
        std::cout << nodo->dato << " ";
        inorden(nodo->der);
    }

    void liberar(Nodo *nodo)
    {
        if (!nodo)
            return;
        liberar(nodo->izq);
        liberar(nodo->der);
        delete nodo;
    }

public:
    ArbolBinario() : raiz(nullptr) {}

    ~ArbolBinario() { liberar(raiz); }

    void insertar(int valor) { insertar(raiz, valor); }

    void mostrar()
    {
        inorden(raiz);
        std::cout << std::endl;
    }
};

int main()
{
    ArbolBinario arbol;

    arbol.insertar(5);
    arbol.insertar(3);
    arbol.insertar(7);

    arbol.mostrar();

    return 0;
}
