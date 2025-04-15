#include <iostream>
#include <ctime>

using std::cout, std::endl;

void print2DMatrix(int **matrix, int size)
{
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      int num = matrix[i][j];

      if (num < 100)
      {
        cout << (num < 10) ? "  " : " ";
      }

      cout << num << " ";
    }
    cout << endl;
  }

  cout << endl;
}

void selectionSort(int **matrix, int size)
{
  int n = size * size;

  for (int i = 0; i < n - 1; i++)
  {
    int minIndex = i;
    int minRow = i / size;
    int minCol = i % size;

    int minValue = matrix[minRow][minCol];

    for (int j = i + 1; j < n; j++)
    {
      int row = j / size;
      int col = j % size;

      if (matrix[row][col] < minValue)
      {
        minValue = matrix[row][col];
        minIndex = j;
        minRow = row;
        minCol = col;
      }
    }

    if (minIndex != i)
    {
      int currentRow = i / size;
      int currentCol = i % size;
      int temp = matrix[currentRow][currentCol];
      matrix[currentRow][currentCol] = matrix[minRow][minCol];
      matrix[minRow][minCol] = temp;
    }
  }
}

int main()
{
  // Use current time as seed for random number generator
  srand(time(NULL));

  int size;
  std::cout << "Ingrese la dimensión de la matriz cuadrada (entre 2 y 8): ";
  std::cin >> size;

  // Validate size is between 2 and 8
  while (size < 2 || size > 8)
  {
    std::cout << "Dimensión inválida. Ingrese un valor entre 2 y 8: ";
    std::cin >> size;
  }

  // Create dynamic 2D array
  int **matrix = new int *[size];
  for (int i = 0; i < size; i++)
  {
    matrix[i] = new int[size];
  }

  // Fill matrix with random numbers between 0 and 100
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      matrix[i][j] = rand() % 101; // 0 to 100
    }
  }

  std::cout << "Matriz original:" << std::endl;
  print2DMatrix(matrix, size);

  // Sort the matrix
  selectionSort(matrix, size);

  std::cout << "Matriz ordenada:" << std::endl;
  print2DMatrix(matrix, size);

  // Free allocated memory
  for (int i = 0; i < size; i++)
  {
    delete[] matrix[i];
  }
  delete[] matrix;

  return 0;
}