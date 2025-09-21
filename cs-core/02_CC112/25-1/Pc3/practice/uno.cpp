#include <iostream>
#include <string>
using namespace std;

void reverse(int *start, int *end)
{
  while (start < end)
  {
    int temp = *start;
    *start = *end;
    *end = temp;

    // Move pointers
    start++;
    end--;
  }
}

void rotateLeft(int *arr, int n, int k)
{
  k = k % n;
  if (k == 0)
    return;

  reverse(arr, arr + k - 1);
  reverse(arr + k, arr + n - 1);
  reverse(arr, arr + n - 1);
}

void rotateRight(int *arr, int n, int k)
{
  k = k % n;
  if (k == 0)
    return;

  reverse(arr, arr + n - 1);
  reverse(arr, arr + k - 1);
  reverse(arr + k, arr + n - 1);
}

int main()
{
  const int MAX_SIZE = 100;
  int arr[MAX_SIZE];
  int n, k;
  string direction;

  cout << "Ingrese el tamaño del arreglo (max 100): ";
  cin >> n;

  if (n <= 0 || n > MAX_SIZE)
  {
    cout << "Tamaño de arreglo no válido." << endl;
    return 1;
  }

  cout << "Ingrese " << n << " elementos:" << endl;
  for (int i = 0; i < n; i++)
  {
    cin >> arr[i];
  }

  cout << "Ingrese el valor de k (cantidad de posiciones a rotar): ";
  cin >> k;

  cout << "¿Rotar hacia la derecha o izquierda?: ";
  cin >> direction;

  if (direction == "derecha")
  {
    rotateRight(arr, n, k);
    cout << "Arreglo rotado a la derecha:" << endl;
  }
  else if (direction == "izquierda")
  {
    rotateLeft(arr, n, k);
    cout << "Arreglo rotado a la izquierda:" << endl;
  }
  else
  {
    cout << "Dirección no válida. Use 'derecha' o 'izquierda'." << endl;
    return 1;
  }

  for (int i = 0; i < n; i++)
  {
    cout << arr[i] << " ";
  }
  cout << endl;

  return 0;
}