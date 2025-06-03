#include <iostream>

using namespace std;

void intercambiar(int &a, int &b)
{
  int temp = a;
  a = b;
  b = temp;
}

void PrintArray(int *vec, int tam, ostream &out)
{
  for (int i = 0; i < tam; ++i)
  {
    out << vec[i] << " ";
  }
  out << endl;
}

void DestroyVector(int *&vec)
{
  delete[] vec;
  vec = nullptr;
}

void CreateVector(int *&vec, int tam)
{
  vec = new int[tam];
}

void ReadArray(int *vec, int tam, istream &in)
{
  for (int i = 0; i < tam; ++i)
  {
    in >> vec[i];
  }
}

void Intercambiar(int *&a, int *&b)
{
  int *temp = a;
  a = b;
  b = temp;
}
// ELIAZ SEBASTIAN BOBADILLA CAMARENA 20244697E

// Función para ordenamiento de burbuja recursivo ascendente
void BurbujaRecursivoAscendente(int *arr, int n)
{
  if (n <= 1)
    return;
  for (int j = 1; j < n; ++j)
  {
    if (arr[j] > arr[0])
    {
      intercambiar(arr[0], arr[j]);
    }
  }
  BurbujaRecursivoAscendente(arr + 1, n - 1);
}

// Función para ordenamiento de burbuja recursivo descendente
void BurbujaRecursivoDescendente(int *arr, int n)
{
  if (n <= 1)
    return;
  for (int j = 1; j < n; ++j)
  {
    if (arr[j] < arr[0])
    {
      intercambiar(arr[0], arr[j]);
    }
  }
  BurbujaRecursivoDescendente(arr + 1, n - 1);
}

int main()
{
  int *vec1 = nullptr, size = 10;
  int *vec2 = nullptr;

  CreateVector(vec1, size);
  ReadArray(vec1, size, cin);
  BurbujaRecursivoAscendente(vec1, size); // Ascendente
  PrintArray(vec1, size, cout);

  CreateVector(vec2, size);
  ReadArray(vec2, size, cin);
  BurbujaRecursivoDescendente(vec2, size); // Descendente
  PrintArray(vec2, size, cout);

  Intercambiar(vec1, vec2); // Intercambiar punteros

  DestroyVector(vec1);
  DestroyVector(vec2);

  return 0;
}