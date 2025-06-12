#include <iostream>
#include <stdexcept>

using std::cout;
using std::endl;
using std::invalid_argument;

class SquareMatrix {
public:
  int n;
  int **rows;

  SquareMatrix(int size) : n(size) {
    if (size <= 0) {
      throw invalid_argument("Size must be greater than 0");
    }

    this->rows = new int *[this->n];

    for (int i = 0; i < this->n; i++) {
      this->rows[i] = new int[this->n];
    }
  }

  ~SquareMatrix() {
    for (int i = 0; i < this->n; i++) {
      delete[] this->rows[i];
    }

    delete[] this->rows;
  }

  void printMatrix() {}
};

int main() {
  int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  cout << "Broski, bro, bro!" << endl;

  return 0;
}
