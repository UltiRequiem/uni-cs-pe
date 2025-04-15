#include <iostream>

using std::cout, std::endl;

void insertionSort(int *numbers, int size)
{
  for (int i = 1; i < size; i++)
  {
    int current = numbers[i];
    int j;

    for (j = i - 1; j >= 0 && numbers[j] > current; j--)
    {
      numbers[j + 1] = numbers[j];
    }

    numbers[j + 1] = current;
  }
}

int main()
{
  int numbers[] = {3, 5, 6, 7, 8, 9, 222, 34454, 111, 3};
  int size = sizeof(numbers) / sizeof(numbers[0]);

  cout << "Original array: ";
  for (int i = 0; i < size; i++)
    cout << numbers[i] << " ";
  cout << endl;

  insertionSort(numbers, size);

  cout << "Sorted array: ";
  for (int i = 0; i < size; i++)
    cout << numbers[i] << " ";
  cout << endl;

  return 0;
}