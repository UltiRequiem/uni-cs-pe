#include <iostream>

struct Nodo
{
    int dato;
    Nodo *sig;
};

void insertarFinal(Nodo *&cabeza, int valor)
{
    Nodo *nuevo = new Nodo{valor, nullptr};

    if (!cabeza)
    {
        cabeza = nuevo;

        return;
    }

    Nodo *temp = cabeza;

    while (temp->sig)
    {
        temp = temp->sig;
    }

    temp->sig = nuevo;
}

void mostrar(Nodo *cabeza)
{
    while (cabeza)
    {
        std::cout << cabeza->dato << " ";
        cabeza = cabeza->sig;
    }
    std::cout << std::endl;
}

void liberar(Nodo *&cabeza)
{
    while (cabeza)
    {
        Nodo *temp = cabeza;
        cabeza = cabeza->sig;
        delete temp;
    }
}

int main()
{
    Nodo *lista = nullptr;

    insertarFinal(lista, 10);
    insertarFinal(lista, 20);
    insertarFinal(lista, 30);

    mostrar(lista);
    liberar(lista);

    return 0;
}
