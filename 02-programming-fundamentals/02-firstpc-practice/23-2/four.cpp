#include <iostream>

void segregateNumbers(const int input[], int size, int output[]) {
  int index = 0;

  for (int i = 0; i < size; ++i) {
    if (input[i] < 0) {
      output[index++] = input[i];
    }
  }

  for (int i = 0; i < size; ++i) {
    if (input[i] >= 0) {
      output[index++] = input[i];
    }
  }
}

int main() {
  int input[] = {9, -3, 5, -2, -8, -6, 1, 3};
  int size = sizeof(input) / sizeof(input[0]);
  int output[size];

  segregateNumbers(input, size, output);

  std::cout << "Salida: ";
  for (int i = 0; i < size; ++i) {
    std::cout << output[i] << " ";
  }

  std::cout << std::endl;

  return 0;
}