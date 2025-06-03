#include <iostream>

using std::cin;
using std::cout;

bool contains(int hayStack[], int hayStackLength, int needle) {
  for (int i = 0; i < hayStackLength; i++) {
    int current = hayStack[i];

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
    int currentInput;

    cout << "Enter a number (0 to stop): ";
    cin >> currentInput;

    if (currentInput == 0) {
      break;
    }
  }

  if (size == 0) {
    input = new int[1];
    input[0] = currentInput;
    size = 1;
    continue;
  }

  size++;

  int *newInput = new int[size];
  int lastElement = input[size - 1];

  if (currentInput > lastElement) {
    for (int i = 0; i < size - 1; i++) {
      newInput[i] = input[i];
    }

    newInput[size - 1] = currentInput;
  } else {
    newInput[0] = currentInput;

    for (int i = 0; i < size - 1; i++) {
      newInput[i + 1] = input[i];
    }
  }

  delete[] input;
  input = newInput;

  for (int i = 0; i < size; i++) {
    cout << input[i] << " ";
  }
}
