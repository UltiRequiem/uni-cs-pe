#include <iostream>

struct Nodo
{
    int clave;

    Nodo *sig;

    Nodo(int c) : clave(c), sig(nullptr) {}
};

class TablaHash
{
    Nodo **tabla;
    int tam;
    int hash(int clave) { return clave % tam; }

public:
    TablaHash(int t) : tam(t)
    {
        tabla = new Nodo *[tam];
        for (int i = 0; i < tam; ++i)
            tabla[i] = nullptr;
    }

    ~TablaHash()
    {
        for (int i = 0; i < tam; ++i)
        {
            Nodo *act = tabla[i];
            while (act)
            {
                Nodo *temp = act;
                act = act->sig;
                delete temp;
            }
        }
        delete[] tabla;
    }

    void insertar(int clave)
    {
        int idx = hash(clave);
        Nodo *nuevo = new Nodo(clave);
        nuevo->sig = tabla[idx];
        tabla[idx] = nuevo;
    }

    bool buscar(int clave)
    {
        int idx = hash(clave);
        Nodo *act = tabla[idx];
        while (act)
        {
            if (act->clave == clave)
                return true;
            act = act->sig;
        }
        return false;
    }
};

int main()
{
    TablaHash t(5);

    t.insertar(10);
    t.insertar(15);
    t.insertar(7);

    std::cout << (t.buscar(15) ? "Encontrado" : "No encontrado") << std::endl;

    return 0;
}
