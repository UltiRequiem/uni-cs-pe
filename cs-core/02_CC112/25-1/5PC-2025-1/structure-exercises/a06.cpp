#include <iostream>

int main()
{
    int x, y, z;
    std::cout << "Dimensiones X Y Z: ";
    std::cin >> x >> y >> z;
    int ***arr = new int **[x];
    for (int i = 0; i < x; ++i)
    {
        arr[i] = new int *[y];
        for (int j = 0; j < y; ++j)
        {
            arr[i][j] = new int[z];
        }
    }
    for (int i = 0; i < x; ++i)
        for (int j = 0; j < y; ++j)
            for (int k = 0; k < z; ++k)
            {
                std::cout << "Valor [" << i << "][" << j << "][" << k << "]: ";
                std::cin >> arr[i][j][k];
            }
    for (int i = 0; i < x; ++i)
        for (int j = 0; j < y; ++j)
            delete[] arr[i][j];
    for (int i = 0; i < x; ++i)
        delete[] arr[i];
    delete[] arr;
    return 0;
}
