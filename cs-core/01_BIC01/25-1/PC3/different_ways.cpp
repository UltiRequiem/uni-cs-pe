#include <iostream>
#include <iterator>

using std::begin;
using std::cout;
using std::distance;
using std::end;
using std::endl;
using std::max_element;

int main()
{
  int arr[3] = {10, 30, 20};
  int *maxPtr = max_element(begin(arr), end(arr));

  // Method 1: Direct array name
  int index1 = distance(arr, maxPtr);

  // Method 2: Using begin()
  int index2 = distance(begin(arr), maxPtr);

  // Method 3: Pointer arithmetic
  int index3 = maxPtr - arr;

  // Output: 1
  cout << "Method 1 (array name): " << index1 << endl;
  // Output: 1
  cout << "Method 2 (begin): " << index2 << endl;
  // Output: 1
  cout << "Method 3 (pointer arithmetic): " << index3 << endl;

  return 0;
}