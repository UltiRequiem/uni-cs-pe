#include <cstring>
#include <iostream>

int main() {
  int n;
  std::cout << "¿Cuántas palabras? ";

  std::cin >> n;
  std::cin.ignore();

  char **arr = new char *[n];

  for (int i = 0; i < n; ++i) {
    char buffer[100];

    std::cout << "Palabra " << (i + 1) << ": ";
    std::cin.getline(buffer, 100);

    arr[i] = new char[strlen(buffer) + 1];
    strcpy(arr[i], buffer);
  }

  std::cout << "\nPalabras ingresadas:\n";

  for (int i = 0; i < n; ++i) {
    std::cout << arr[i] << std::endl;
    delete[] arr[i];
  }

  delete[] arr;

  return 0;
}
