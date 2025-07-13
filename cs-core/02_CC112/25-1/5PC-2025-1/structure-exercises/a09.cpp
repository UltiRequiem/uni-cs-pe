#include <iostream>

template <typename T>
class Array
{
    T *datos;
    int tam;

public:
    Array(int n) : tam(n) { datos = new T[tam]; }

    ~Array() { delete[] datos; }

    T &operator[](int i) { return datos[i]; }

    int size() const { return tam; }
};

int main()
{
    Array<int> a(3);
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;

    for (int i = 0; i < a.size(); ++i)
    {
        std::cout << a[i] << " ";
    }

    std::cout << std::endl;

    Array<float> b(2);

    b[0] = 1.5f;
    b[1] = 2.5f;

    for (int i = 0; i < b.size(); ++i)
    {
        std::cout << b[i] << " ";
    }

    std::cout << std::endl;
    return 0;
}
