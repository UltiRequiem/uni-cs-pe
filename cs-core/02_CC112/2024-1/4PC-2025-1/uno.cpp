#include <stdexcept>

using std::invalid_argument;

class Fraction {
public:
  int numerator;
  int denominator;

  Fraction(int numerator, int denominator = 1) {
    if (denominator == 0) {
      throw invalid_argument("Denominator cannot be zero");
    }

    // El que llevara el signo es el numerador.
    int symbol = numerator * denominator < 0 ? -1 : 1;

    this->denominator = abs(denominator);
    this->numerator = abs(numerator) * symbol;
  }
};
