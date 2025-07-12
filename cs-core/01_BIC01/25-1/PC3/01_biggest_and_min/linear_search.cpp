#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main()
{
  const int inputLength = 3;
  int inputArray[inputLength];

  for (int i = 0; i < inputLength; i++)
  {
    cout << "Enter value for element " << i + 1 << ": ";
    cin >> inputArray[i];
  }

  int minNumber = inputArray[0];
  int maxNumber = inputArray[0];

  for (int i = 1; i < inputLength; i++)
  {
    if (inputArray[i] < minNumber)
    {
      minNumber = inputArray[i];
    }
    if (inputArray[i] > maxNumber)
    {
      maxNumber = inputArray[i];
    }
  }

  cout << "The minimum number is " << minNumber << endl;
  cout << "The maximum number is " << maxNumber << endl;

  return 0;
}