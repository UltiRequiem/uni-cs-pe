#include <iostream>

using std::cout, std::endl;

void bubbleSort(int *numbers, int size)
{

  for (int i = 0; i < size - 1; i++)
  {
    for (int j = 0; j < size - i - 1; j++)
    {
      int current = numbers[j];
      int next = numbers[j + 1];
      if (current > next)
      {
        numbers[j + 1] = current;
        numbers[j] = next;
        // we can use std::swap, but i want to keept it old school
      }
    }
  }
}

int main()
{
  int numbers[] = {5, 7, 8, 9, 2, 1, 3, 534, 23455, 545522, 222};
  int numbersSize = sizeof(numbers) / sizeof(numbers[0]);

  bubbleSort(numbers, numbersSize);

  for (int i = 0; i < numbersSize; i++)
  {
    cout << numbers[i] << " ";
  }
  cout << endl;

  return 0;
}