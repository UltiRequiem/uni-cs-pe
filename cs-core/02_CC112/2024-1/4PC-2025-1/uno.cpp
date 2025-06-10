#include <stdexcept>
#include <string>

using std::invalid_argument;
using std::string;
using std::to_string;

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
    this->reduce();
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

  string toString() const {
    if (this->denominator == 0) {
      return "0";
    }

    if (this->numerator == this->denominator) {
      return "1";
    }

    return to_string(this->numerator) + "/" + to_string(this->denominator);
  }

  bool operator==(const Fraction &other) const {
    return this->numerator == other.numerator &&
           this->denominator == other.denominator;
  }

  Fraction &operator=(const Fraction &other) {
    if (this != &other) {
      this->numerator = other.numerator;
      this->denominator = other.denominator;
      this->reduce();
    }

    return *this;
  }

private:
  void reduce() {
    int gcd = this->gcd(this->numerator, this->denominator);
    if (gcd != 0) {
      this->numerator /= gcd;
      this->denominator /= gcd;
    }
  }

  // a = b * q + r => gcd(a, b) = gcd(b, r)
  int gcd(int a, int b) const {
    while (b != 0) {
      int temp = b;
      b = a % b;
      a = temp;
    }

    return a;
  }
};
