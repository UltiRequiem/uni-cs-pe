#include <iostream>

using std::begin;
using std::cin;
using std::cout;
using std::distance;
using std::end;
using std::endl;
using std::max_element;
using std::min_element;

int main()
{
  const int inputLength = 3;
  int inputArray[inputLength];

  for (int i = 0; i < inputLength; i++)
  {
    cout << "Enter value for element " << i + 1 << ": ";
    cin >> inputArray[i];
  }

  int *maxNumber = max_element(begin(inputArray), end(inputArray));
  int *minElement = min_element(begin(inputArray), end(inputArray));

  int maxIndex = distance(inputArray, maxNumber);
  int minIndex = distance(inputArray, minElement);

  cout << "The maximum number is: " << *maxNumber << " at index " << maxIndex << endl;
  cout << "The minimum number is: " << *minElement << " at index " << minIndex << endl;

  return 0;
}