#include <iostream>
#include <cstring>

class ArchivoVirtual
{
    char *buffer;
    int capacidad;

public:
    ArchivoVirtual(int cap) : capacidad(cap)
    {
        buffer = new char[capacidad];
        buffer[0] = '\0';
    }
    ~ArchivoVirtual() { delete[] buffer; }
    void escribir(const char *texto)
    {
        if ((int)strlen(texto) >= capacidad)
        {
            int nuevaCap = capacidad * 2 + strlen(texto);
            char *nuevo = new char[nuevaCap];
            strcpy(nuevo, buffer);
            strcat(nuevo, texto);
            delete[] buffer;
            buffer = nuevo;
            capacidad = nuevaCap;
        }
        else
        {
            strcat(buffer, texto);
        }
    }
    void mostrar() const
    {
        std::cout << buffer << std::endl;
    }
};

int main()
{
    ArchivoVirtual arch(10);
    arch.escribir("Hola, ");
    arch.escribir("mundo!");
    arch.mostrar();
    return 0;
}
