#include <iostream>

using std::cout, std::endl;

int binarySearch(int *haystack, int size, int needle)
{
  int low = 0;
  int high = size - 1;

  while (low <= high)
  {
    int mid = (low + high) / 2;

    if (haystack[mid] == needle)
    {
      return mid;
    }

    if (haystack[mid] > needle)
    {
      high = mid - 1;
    }
    else
    {
      low = mid + 1;
    }
  }

  return -1;
}

int main()
{
  int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int numbersSize = sizeof(numbers) / sizeof(numbers[0]);

  cout << "Value found at index " << binarySearch(numbers, numbersSize, 9) << endl;
  return 0;
}