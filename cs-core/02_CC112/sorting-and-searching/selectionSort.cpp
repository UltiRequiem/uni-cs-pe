#include <iostream>
using std::endl, std::cout;

void selectionSort(int *numbers, int size)
{
  for (int i = 0; i < size; i++)
  {
    int minNumber = numbers[i];
    int minNumberIndex = i;

    for (int j = i + 1; j < size; j++)
    {
      int tentativeMin = numbers[j];

      if (tentativeMin < minNumber)
      {
        minNumber = tentativeMin;
        minNumberIndex = j;
      }
    }

    int current = numbers[i];

    numbers[i] = minNumber;
    numbers[minNumberIndex] = current;
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

  selectionSort(numbers, size);

  cout << "Sorted array: ";
  for (int i = 0; i < size; i++)
    cout << numbers[i] << " ";
  cout << endl;

  return 0;
}