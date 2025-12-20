#include <iostream>

using namespace std;

bool contains(int arr[], int size, int value) {
  for (int i = 0; i < size; i++) {
    if (arr[i] == value) {
      return true;
    }
  }

  return false;
}

int main() {
  int input[] = {2, 3, 3, 4, 1, 5, 4, 2, 1, 3, 0};
  int inputLength = sizeof(input) / sizeof(input[0]);

  int *arr = nullptr;
  int size = 0;

  for (int i = 0; i < inputLength; i++) {
    int current = input[i];

    if (current <= 0) {
      continue;
    }

    if (contains(arr, size, current)) {
      continue;
    }

    if (size == 0) {
      arr = new int[1];
      arr[0] = current;
      size = 1;
    } else {
      if (current > arr[size - 1]) {
        int *newArr = new int[size + 1];

        for (int j = 0; j < size; j++) {
          newArr[j] = arr[j];
        }

        newArr[size] = current;
        delete[] arr;
        arr = newArr;
        size++;
      } else {
        int *newArr = new int[size + 1];
        newArr[0] = current;

        for (int j = 0; j < size; j++) {
          newArr[j + 1] = arr[j];
        }

        delete[] arr;
        arr = newArr;
        size++;
      }
    }
  }

  cout << "Arreglo formado: ";
  for (int i = 0; i < size; i++) {
    cout << arr[i] << " ";
  }
  cout << endl;

  if (size > 0) {
    cout << "Maximo: " << arr[size - 1] << endl;
  } else {
    cout << "Maximo: no existe" << endl;
  }

  if (arr != nullptr) {
    delete[] arr;
  }

  return 0;
}
