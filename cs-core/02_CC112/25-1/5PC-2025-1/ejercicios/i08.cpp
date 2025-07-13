#include <iostream>
#include <cstring>

int main()
{
    char frase[200];
    std::cout << "Ingrese una frase: ";

    std::cin.getline(frase, 200);

    int palabras = 0;

    for (int i = 0; frase[i]; ++i)
    {
        if (frase[i] == ' ')
            ++palabras;
    }

    ++palabras;

    char **arr = new char *[palabras];
    int idx = 0;

    char *token = strtok(frase, " ");

    while (token)
    {
        arr[idx] = new char[strlen(token) + 1];
        strcpy(arr[idx], token);
        ++idx;
        token = strtok(nullptr, " ");
    }

    std::cout << "Palabras:\n";

    for (int i = 0; i < palabras; ++i)
    {
        std::cout << arr[i] << std::endl;
        delete[] arr[i];
    }

    delete[] arr;
    return 0;
}
