#include <iostream>
#include <cstring>

class Buffer
{
    char *datos;
    int tam;

public:
    Buffer(int t) : tam(t)
    {
        datos = new char[tam];
        std::memset(datos, 0, tam);
    }

    ~Buffer() { delete[] datos; }

    Buffer(const Buffer &other) : tam(other.tam)
    {
        datos = new char[tam];
        std::memcpy(datos, other.datos, tam);
    }

    Buffer &operator=(const Buffer &other)
    {
        if (this != &other)
        {
            delete[] datos;
            tam = other.tam;
            datos = new char[tam];
            std::memcpy(datos, other.datos, tam);
        }
        return *this;
    }

    Buffer(Buffer &&other) noexcept : datos(other.datos), tam(other.tam)
    {
        other.datos = nullptr;
        other.tam = 0;
    }

    Buffer &operator=(Buffer &&other) noexcept
    {
        if (this != &other)
        {
            delete[] datos;
            datos = other.datos;
            tam = other.tam;
            other.datos = nullptr;
            other.tam = 0;
        }

        return *this;
    }
};

int main()
{
    Buffer b1(10);
    Buffer b2 = b1;
    Buffer b3(5);
    b3 = std::move(b1);
    return 0;
}
