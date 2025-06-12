#include <iostream>
#include <stdexcept>

using std::cout;
using std::endl;
using std::fabs;
using std::invalid_argument;

class SquareMatrix {
public:
  int n;
  double **rows;

  SquareMatrix(int size) : n(size) {
    if (size <= 0) {
      throw invalid_argument("Size must be greater than 0");
    }

    this->rows = new double *[this->n];

    for (int i = 0; i < this->n; i++) {
      this->rows[i] = new double[this->n];
    }
  }

  ~SquareMatrix() {
    for (int i = 0; i < this->n; i++) {
      delete[] this->rows[i];
    }

    delete[] this->rows;
  }

  // We print a full row, then the next one, etc..
  void printMatrix() const {
    for (int i = 0; i < this->n; i++) {
      for (int j = 0; j < this->n; j++) {
        double actualValue = this->rows[i][j];

        if (fabs(actualValue) < 1e-10) {
          actualValue = 0.0;
        }

        cout << actualValue << "\t";
      }

      cout << endl;
    }
  }

  void fillMatrix(double *input, int inputSize) {
    // This is a square matrix
    if (inputSize != this->n * this->n) {
      throw invalid_argument("Input size does not match matrix size");
    }

    for (int i = 0; i < this->n; i++) {
      double *currentRow = this->rows[i];

      for (int j = 0; j < this->n; j++) {
        currentRow[j] = input[i * this->n + j];
      }
    }
  }

  // A: Singular matrix => det(A) = 0
  int gaussElimination() {
    int rowSwapCount = 0;
    for (int i = 0; i < this->n; i++) {
      int maxRow = i;

      for (int k = i + 1; k < this->n; k++) {
        if (fabs(this->rows[k][i]) > fabs(this->rows[maxRow][i])) {
          maxRow = k;
        }
      }

      if (fabs(this->rows[maxRow][i]) < 1e-10) {
        throw invalid_argument(
            "Matrix is singular, cannot perform Gauss elimination");
      }

      if (maxRow != i) {
        double *temp = this->rows[i];
        this->rows[i] = this->rows[maxRow];
        this->rows[maxRow] = temp;
        rowSwapCount++; // Increment swap count
      }

      double pivot = this->rows[i][i];

      for (int j = i + 1; j < this->n; j++) {
        double factor = this->rows[j][i] / pivot;

        for (int k = i; k < this->n; k++) {
          this->rows[j][k] -= factor * this->rows[i][k];

          // Clean up very small numbers (floating point precision issues)
          if (fabs(this->rows[j][k]) < 1e-10) {
            this->rows[j][k] = 0.0;
          }
        }
      }
    }
    return rowSwapCount; // Return the number of swaps performed
  }

  double determinant3x3() {
    if (this->n != 3) {
      throw invalid_argument("Determinant can only be calculated for 3x3 "
                             "matrices in this implementation");
    }

    auto matrix = this->rows;

    return matrix[0][0] *
               (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) -
           matrix[0][1] *
               (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) +
           matrix[0][2] *
               (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
  }

  double determinantFromUpperTriangular(int swapCount) {
    double det = 1.0;
    for (int i = 0; i < this->n; i++) {
      det *= this->rows[i][i];
    }

    if (swapCount % 2 == 1) {
      det = -det;
    }

    return det;
  }
};

int main() {
  // double singularMatrix[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  double numbers[] = {2, 1, 3, 1, 3, 2, 3, 2, 1};

  int numbersSize = sizeof(numbers) / sizeof(numbers[0]);

  SquareMatrix matrix(3);

  matrix.fillMatrix(numbers, numbersSize);

  cout << "Original Matrix:" << endl;
  matrix.printMatrix();

  if (matrix.n == 3) {
    cout << "Determinant of original matrix: " << matrix.determinant3x3()
         << endl;
  }

  cout << endl << "Performing Gauss elimination..." << endl;

  int swapCount = matrix.gaussElimination();

  cout << "Matrix after Gauss elimination (Upper triangular form):" << endl;
  matrix.printMatrix();

  cout << "Number of row swaps performed: " << swapCount << endl;

  double diagonalProduct = 1.0;
  for (int i = 0; i < matrix.n; i++) {
    diagonalProduct *= matrix.rows[i][i];
  }
  cout << "Product of diagonal elements: " << diagonalProduct << endl;
  cout << "Sign adjustment for " << swapCount
       << " swaps: " << (swapCount % 2 == 1 ? "negative" : "positive") << endl;

  cout << "Determinant from upper triangular matrix: "
       << matrix.determinantFromUpperTriangular(swapCount) << endl;

  return 0;
}
