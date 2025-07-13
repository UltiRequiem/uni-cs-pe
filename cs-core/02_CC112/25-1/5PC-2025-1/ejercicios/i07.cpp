#include <iostream>

void asignar(int **p)
{
    *p = new int;
    **p = 123;
}

int main()
{
    int *ptr = nullptr;
    asignar(&ptr);

    std::cout << "Valor asignado: " << *ptr << std::endl;

    delete ptr;

    return 0;
}
