#include <iostream>
#include <cstring>

using std::cout;
using std::endl;

class Cadena
{
  char *buffer;

public:
  Cadena(const char *texto)
  {
    buffer = new char[strlen(texto) + 1];
    strcpy(buffer, texto);
  }

  ~Cadena() { delete[] buffer; }

  void set(const char *texto) { strcpy(buffer, texto); }
  void print() const { cout << buffer << endl; }
};

void copiarPorValor(Cadena c)
{
  c.set("Modificado");
  c.print();
}

int main()
{
  Cadena c1("Original");

  copiarPorValor(c1);
  c1.print();

  return 0;
}
