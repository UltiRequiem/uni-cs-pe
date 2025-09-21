#include <iostream>

using namespace std;

double valorasbsoluto(double x)
{
  return x * ((x > 0) - (x < 0));
}

int redondeador(double x)
{
  if (x >= 0.0)
    return static_cast<int>(x + 0.5);
  else
    return static_cast<int>(x - 0.5);
}

double determinant(const double *A, int n)
{
  if (n == 1)
  {
    return A[0];
  }

  int bestRow = 0, maxZeros = -1;
  for (int i = 0; i < n; ++i)
  {
    int zeroCount = 0;
    for (int j = 0; j < n; ++j)
    {
      if (A[i * n + j] == 0.0)
        ++zeroCount;
    }
    if (zeroCount == n)
    {
      return 0.0;
    }
    if (zeroCount > maxZeros)
    {
      maxZeros = zeroCount;
      bestRow = i;
    }
  }

  double det = 0.0;
  double *sub = new double[(n - 1) * (n - 1)];

  for (int j = 0; j < n; ++j)
  {
    double val = A[bestRow * n + j];
    if (val == 0.0)
      continue;

    for (int r = 0, si = 0; r < n; ++r)
    {
      if (r == bestRow)
        continue;
      for (int c = 0, sj = 0; c < n; ++c)
      {
        if (c == j)
          continue;
        sub[si * (n - 1) + sj] = A[r * n + c];
        ++sj;
      }
      ++si;
    }

    double sign = ((bestRow + j) % 2 == 0) ? 1.0 : -1.0;
    det += sign * val * determinant(sub, n - 1);
  }

  delete[] sub;
  return det;
}
// ELIAZ SEBASTIAN BOBADILLA CAMARENA 20244697E

int main()
{
  int n;
  cout << "Ingrese el tamaño de la matriz (máximo 10): ";
  if (!(cin >> n) || n < 1 || n > 10)
  {
    cout << "Tamaño inválido. Debe ser entre 1 y 10.\n";
    return 1;
  }

  double *A = new double[n * n];
  cout << "Ingrese los " << (n * n) << " elementos de la matriz:\n";
  for (int i = 0; i < n * n; ++i)
  {
    cin >> A[i];
  }

  double det = determinant(A, n);
  double absDiff = valorasbsoluto(det - redondeador(det));
  if (absDiff < 1e-9)
  {
    cout << "Determinante = " << redondeador(det) << "\n";
  }
  else
  {
    cout << "Determinante = " << det << "\n";
  }

  delete[] A;
  return 0;
}
