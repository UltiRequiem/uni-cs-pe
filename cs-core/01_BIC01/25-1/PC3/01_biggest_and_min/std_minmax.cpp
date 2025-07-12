#include <iostream>
#include <algorithm>
#include <utility>

using std::cin;
using std::cout;
using std::endl;
using std::minmax_element;
using std::pair;

int main()
{
  const int inputLength = 3;
  int inputArray[inputLength];

  for (int i = 0; i < inputLength; i++)
  {
    cout << "Enter value for element " << i + 1 << ": ";
    cin >> inputArray[i];
  }

  pair<int *, int *> result = minmax_element(inputArray, inputArray + inputLength);
  int minNumber = *result.first;
  int maxNumber = *result.second;

  cout << "The minimum number is " << minNumber << endl;
  cout << "The maximum number is " << maxNumber << endl;

  return 0;
}