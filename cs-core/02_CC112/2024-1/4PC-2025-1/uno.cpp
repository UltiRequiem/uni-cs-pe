#include <stdexcept>

using std::invalid_argument;

class Fraction {
public:
  int numerator;
  int denominator;

  Fraction(int numerator = 0, int denominator = 1) {
    if (denominator == 0) {
      throw invalid_argument("Denominator cannot be zero");
    }

    // El que llevara el signo es el numerador.
    int symbol = numerator * denominator < 0 ? -1 : 1;

    this->denominator = abs(denominator);
    this->numerator = abs(numerator) * symbol;
  }

  Fraction difference(const Fraction &other) const {
    int commonDenominator = this->denominator * other.denominator;
    int newNumerator = (this->numerator * other.denominator) -
                       (other.numerator * this->denominator);

    return Fraction(newNumerator, commonDenominator);
  }

  Fraction product(const Fraction &other) const {
    return Fraction(this->denominator * other.denominator,
                    this->numerator * other.numerator);
  }

  Fraction division(const Fraction &other) const {
    if (other.numerator == 0) {
      throw invalid_argument("Cannot divide by zero");
    }
    return Fraction(this->numerator * other.denominator,
                    this->denominator * other.numerator);
  }
};
