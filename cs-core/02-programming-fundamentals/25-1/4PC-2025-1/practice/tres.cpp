#include <iostream>
#define MAX 100

void imprimirSecuenciaImpar(int lista[MAX], int n)
{
  int *p = lista;
  int inicioActual = -1;
  int longitudActual = 0;
  int inicioMax = -1;
  int longitudMax = 0;

  for (int i = 0; i < n; i++)
  {
    if (*(p + i) % 2 != 0)
    {
      if (inicioActual == -1)
      {
        inicioActual = i;
        longitudActual = 1;
      }
      else
      {
        longitudActual++;
      }
    }
    else
    {
      if (inicioActual != -1)
      {
        if (longitudActual > longitudMax)
        {
          longitudMax = longitudActual;
          inicioMax = inicioActual;
        }
        inicioActual = -1;
        longitudActual = 0;
      }
    }
  }

  if (longitudActual > longitudMax)
  {
    longitudMax = longitudActual;
    inicioMax = inicioActual;
  }

  if (longitudMax > 0)
  {
    std::cout << "La secuencia impar más larga es: [";
    for (int i = inicioMax; i < inicioMax + longitudMax; i++)
    {
      std::cout << *(p + i);
      if (i < inicioMax + longitudMax - 1)
      {
        std::cout << ", ";
      }
    }
    std::cout << "]" << std::endl;
  }
  else
  {
    std::cout << "No existe secuencia impar." << std::endl;
  }
}

int main()
{
  int lista[MAX] = {1, 2, 3, 2, 2, 1, 1, 3, 3, 7, 5, 1, 2, 3};
  int n = 14;
  imprimirSecuenciaImpar(lista, n);

  return 0;
}
