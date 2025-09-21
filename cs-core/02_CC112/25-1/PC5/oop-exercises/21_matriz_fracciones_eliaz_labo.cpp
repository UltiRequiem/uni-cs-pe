/*
Este problema vino el 24-1, lo hice practicando para la cuarta pc y no vino
Le dejo algunas notas de como lo hice esa vez.

https://github.com/UltiRequiem/uni-cs-pe/blob/main/cs-core/02_CC112/24-1/4PC-2025-1/integerGaussElimination.cpp
https://github.com/UltiRequiem/uni-cs-pe/blob/main/cs-core/02_CC112/24-1/4PC-2025-1/gauss_elimination_notes.jpg
*/

#include <iostream>
#include <stdexcept>
#include <string>

using std::cout;
using std::endl;
using std::invalid_argument;
using std::string;
using std::to_string;

class Fraction
{
public:
  int numerator;
  int denominator;

  Fraction(int numerator = 0, int denominator = 1)
  {
    if (denominator == 0)
    {
      throw invalid_argument("Denominator cannot be zero");
    }

    // El que llevara el signo es el numerador.
    int symbol = numerator * denominator < 0 ? -1 : 1;

    this->denominator = abs(denominator);
    this->numerator = abs(numerator) * symbol;
    this->reduce();
  }

  Fraction difference(const Fraction &other) const
  {
    int commonDenominator = this->denominator * other.denominator;
    int newNumerator = (this->numerator * other.denominator) -
                       (other.numerator * this->denominator);

    return Fraction(newNumerator, commonDenominator);
  }

  Fraction product(const Fraction &other) const
  {
    return Fraction(this->numerator * other.numerator,
                    this->denominator * other.denominator);
  }

  Fraction division(const Fraction &other) const
  {
    if (other.numerator == 0)
    {
      throw invalid_argument("Cannot divide by zero");
    }

    return Fraction(this->numerator * other.denominator,
                    this->denominator * other.numerator);
  }

  string toString() const
  {
    if (this->numerator == 0)
    {
      return "0";
    }

    if (this->numerator == this->denominator)
    {
      return "1";
    }

    if (this->denominator == 1)
    {
      return to_string(this->numerator);
    }

    return to_string(this->numerator) + "/" + to_string(this->denominator);
  }

  bool operator==(const Fraction &other) const
  {
    return this->numerator == other.numerator &&
           this->denominator == other.denominator;
  }

  Fraction &operator=(const Fraction &other)
  {
    if (this != &other)
    {
      this->numerator = other.numerator;
      this->denominator = other.denominator;
      this->reduce();
    }

    return *this;
  }

private:
  void reduce()
  {
    int gcd = this->gcd(this->numerator, this->denominator);
    if (gcd != 0)
    {
      this->numerator /= gcd;
      this->denominator /= gcd;
    }
  }

  // a = b * q + r => gcd(a, b) = gcd(b, r)
  int gcd(int a, int b) const
  {
    while (b != 0)
    {
      int temp = b;
      b = a % b;
      a = temp;
    }

    return a;
  }
};

class Matrix
{
public:
  int n;
  Fraction **Mat;

  Matrix(int size) : n(size)
  {
    if (size <= 0)
    {
      throw invalid_argument("Size must be greater than zero");
    }

    this->Mat = new Fraction *[this->n];

    for (int i = 0; i < this->n; ++i)
    {
      Mat[i] = new Fraction[this->n];
    }
  }

  ~Matrix()
  {
    for (int i = 0; i < this->n; ++i)
    {
      delete[] Mat[i];
    }

    delete[] Mat;
  }

  void fillMatrix(Fraction input[], int inputSize)
  {
    if (inputSize != this->n * this->n)
    {
      throw invalid_argument("Input size does not match matrix size");
    }

    for (int i = 0; i < this->n; ++i)
    {
      for (int j = 0; j < this->n; ++j)
      {
        Mat[i][j] = input[i * this->n + j];
      }
    }
  }

  void printMatrix()
  {
    for (int i = 0; i < this->n; i++)
    {
      for (int j = 0; j < this->n; j++)
      {
        Fraction &actualValue = Mat[i][j];

        cout << actualValue.toString() << "\t";
      }

      cout << endl;
    }
  }

  void GaussElimination()
  {
    for (int i = 0; i < this->n; ++i)
    {
      auto pivot = Mat[i][i];

      if (pivot.numerator == 0)
      {
        continue;
      }

      for (int j = i + 1; j < this->n; ++j)
      {
        auto factor = Mat[j][i].division(pivot);

        for (int k = i; k < this->n; ++k)
        {
          auto product = factor.product(Mat[i][k]);
          Mat[j][k] = Mat[j][k].difference(product);
        }
      }
    }
  }
};

int main()
{
  int n = 3;

  Fraction input[] = {{1, 1}, {1, 2}, {1, 3}, {1, 1}, {5, 6}, {7, 12}, {1, 2}, {1, 4}, {11, 30}};

  // Fraction input[] = {{1, 1}, {2, 1}, {3, 1},  {2, 1}, {5, 1},
  //                     {8, 1}, {4, 1}, {10, 1}, {20, 1}};

  int inputSize = sizeof(input) / sizeof(input[0]);

  Matrix matriz(n);
  matriz.fillMatrix(input, inputSize);

  cout << "Matriz original:\n";
  matriz.printMatrix();

  matriz.GaussElimination();

  cout << "\nMatriz escalonada:\n";
  matriz.printMatrix();

  return 0;
}