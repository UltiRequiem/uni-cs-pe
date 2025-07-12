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

  for (int j = 0; j < inputLength; j++)
  {
    int currentNum = inputArray[j];

    for (int y = j; y < inputLength; y++)
    {
      int innerCycle = inputArray[y];

      if (currentNum > innerCycle)
      {
        inputArray[y] = currentNum;
        inputArray[j] = innerCycle;
      }
    }
  }

  int minNumber = inputArray[0];
  int maxNumber = inputArray[inputLength - 1];

  cout << "The minimum number is " << minNumber << endl;
  cout << "The maximum number is " << maxNumber << endl;

  return 0;
}