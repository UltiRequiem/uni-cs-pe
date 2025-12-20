#include <iostream>
#include <cstring>

class Diccionario
{
    char **palabras;
    int cantidad;

public:
    Diccionario(int n) : cantidad(n)
    {
        palabras = new char *[cantidad];
        for (int i = 0; i < cantidad; ++i)
            palabras[i] = nullptr;
    }

    ~Diccionario()
    {
        for (int i = 0; i < cantidad; ++i)
            delete[] palabras[i];
        delete[] palabras;
    }

    void agregar(int idx, const char *palabra)
    {
        palabras[idx] = new char[strlen(palabra) + 1];
        strcpy(palabras[idx], palabra);
    }

    void mostrar() const
    {
        for (int i = 0; i < cantidad; ++i)
            if (palabras[i])
                std::cout << palabras[i] << std::endl;
    }
};

int main()
{
    int n;

    std::cout << "¿Cuántas palabras? ";
    std::cin >> n;
    std::cin.ignore();

    Diccionario d(n);

    for (int i = 0; i < n; ++i)
    {
        char buffer[100];
        std::cout << "Palabra " << (i + 1) << ": ";
        std::cin.getline(buffer, 100);
        d.agregar(i, buffer);
    }

    d.mostrar();

    return 0;
}
