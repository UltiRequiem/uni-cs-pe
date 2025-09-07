#include <iostream>

using namespace std;

class Compra {
public:
  int p1;
  int p2;
  int dinero;

  Compra(int p1, int p2, int dinero) {
    this->p1 = p1;
    this->p2 = p2;
    this->dinero = dinero;
  }

  void printResults() {
    cout << "c1 c2   compra" << endl;

    for (int c1 = 1; c1 * p1 <= dinero; c1++) {
      for (int c2 = 1; this->p1 * c1 + this->p2 * c2 <= this->dinero; c2++) {
        cout << c1 << "  " << c2 << " " << c1 * p1 + c2 * p2 << endl;
      }
    }
  }
};

int main() {
  Compra uno(10, 20, 60);

  uno.printResults();
}
