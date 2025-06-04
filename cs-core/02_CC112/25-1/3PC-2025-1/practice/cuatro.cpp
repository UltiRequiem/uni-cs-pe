#include <iostream>

int EsNombreValido(char *p)
{
  if (!isalpha(p[0]) && p[0] != '_')
  {
    return 1;
  }

  for (int i = 0; i < strlen(p); i++)
  {
    if (!isalnum(p[i]) && p[i] != '_')
    {
      return i + 1;
    }

    if (p[i] == '_' && p[i + 1] == '_')
    {
      return i + 1;
    }
  }

  return 0;
}

int main()
{
  char nombre1[] = "mi_variable1";
  char nombre2[] = "1variable";
  char nombre3[] = "var name";
  char nombre4[] = "var__name";

  std::cout << "EsNombreValido(\"mi_variable1\"): " << EsNombreValido(nombre1) << std::endl;
  std::cout << "EsNombreValido(\"1variable\"): " << EsNombreValido(nombre2) << std::endl;
  std::cout << "EsNombreValido(\"var name\"): " << EsNombreValido(nombre3) << std::endl;
  std::cout << "EsNombreValido(\"var__name\"): " << EsNombreValido(nombre4) << std::endl;

  return 0;
}
