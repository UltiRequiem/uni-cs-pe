#include <iostream>
#include <cmath>

int *merge(int *left, int leftSize, int *right, int rightSize)
{
  int *result = new int[leftSize + rightSize];

  int leftIndex = 0;
  int rightIndex = 0;
  int resultIndex = 0;

  while (leftIndex < leftSize && rightIndex < rightSize)
  {
    int currentLeft = left[leftIndex];
    int currentRight = right[rightIndex];

    if (currentLeft <= currentRight)
    {
      result[resultIndex++] = currentLeft;
      leftIndex++;
      continue;
    }

    result[resultIndex++] = currentRight;
    rightIndex++;
  }

  while (leftIndex < leftSize)
  {
    result[resultIndex++] = left[leftIndex++];
  }

  while (rightIndex < rightSize)
  {
    result[resultIndex++] = right[rightIndex++];
  }

  return result;
}

int *mergeSort(int *nums, int size)
{
  if (size <= 1)
  {
    int *result = new int[size];

    for (int i = 0; i < size; i++)

    {
      result[i] = nums[i];
    }

    return result;
  }

  int pivot = floor(size / 2);

  int *left = new int[pivot];
  int *right = new int[size - pivot];

  for (int i = 0; i < pivot; i++)
  {
    left[i] = nums[i];
  }

  for (int i = pivot; i < size; i++)
  {
    right[i - pivot] = nums[i];
  }

  int *sortedLeft = mergeSort(left, pivot);
  int *sortedRight = mergeSort(right, size - pivot);

  delete[] left;
  delete[] right;

  int *result = merge(sortedLeft, pivot, sortedRight, size - pivot);

  delete[] sortedLeft;
  delete[] sortedRight;

  return result;
}

int main()
{
  int arr[] = {38, 27, 43, 3, 9, 82, 10};
  int size = sizeof(arr) / sizeof(arr[0]);

  int *sorted = mergeSort(arr, size);

  std::cout << "Sorted array: ";

  for (int i = 0; i < size; i++)
  {
    std::cout << sorted[i] << " ";
  }

  std::cout << std::endl;

  delete[] sorted;

  return 0;
}