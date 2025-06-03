#include <iostream>

using std::cin;
using std::cout;
using std::endl;

bool includes(int array[], int arrayLength, int needle) {
  for (int i = 0; i < arrayLength; i++) {
    int current = array[i];

    if (current == needle) {
      return true;
    }
  }

  return false;
}

int main() {
  int *input = nullptr;
  int size = 0;

  while (true) {
    cout << "Enter a number (0 to stop): ";
    int currentInput;
    cin >> currentInput;

    if (currentInput == 0) {
      break;
    }

    if (size == 0) {
      input = new int[1];
      input[0] = currentInput;
      size = 1;
      continue;
    }

    int *newArray = new int[size + 1];

    for (int i = 0; i < size; i++) {
      newArray[i] = input[i];
    }

    newArray[size] = currentInput;
    delete[] input;
    input = newArray;
    size++;
  }

  if (size == 0) {
    return 0;
  }

  cout << "Arreglo formado: ";

  for (int i = 0; i < size; i++) {
    cout << input[i] << " ";
  }

  cout << endl;

  int *result = nullptr;
  int resultSize = 0;

  for (int j = 0; j < size; j++) {
    int current = input[j];

    if (resultSize == 0) {
      result = new int[1];
      result[0] = current;
      resultSize = 1;
      continue;
    }

    if (includes(result, resultSize, current)) {
      continue;
    }

    int lastElement = result[resultSize - 1];

    if (current > lastElement) {
      int *newArray = new int[resultSize + 1];

      for (int k = 0; k < resultSize; k++) {
        newArray[k] = result[k];
      }

      newArray[resultSize] = current;

      resultSize++;
      delete[] result;
      result = newArray;
    } else {
      int *newArray = new int[resultSize + 1];

      newArray[0] = current;

      for (int k = 0; k < resultSize; k++) {
        newArray[k + 1] = result[k];
      }

      delete[] result;
      result = newArray;

      resultSize++;
    }
  }

  cout << "Resultado: ";

  for (int j = 0; j < resultSize; j++) {
    int currentResultItem = result[j];

    cout << currentResultItem << " ";
  }

  cout << endl;

  return 0;
}
