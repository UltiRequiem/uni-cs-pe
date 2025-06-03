// ELIAZ SEBASTIAN BOBADILLA CAMARENA 20244697E

#include <iostream>
using namespace std;

bool isAlnumChar(char c)
{
  return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

int main()
{
  const int MAXLEN = 1000;
  char *input = new char[MAXLEN + 1];

  cout << "Ingrese una cadena:\n";
  cin.getline(input, MAXLEN);

  char *clean = new char[MAXLEN + 1];
  char *src = input;
  char *dst = clean;
  while (*src)
  {
    if (isAlnumChar(*src))
    {
      *dst++ = *src;
    }
    ++src;
  }
  *dst = '\0';
  delete[] input;

  int len = 0;
  for (char *p = clean; *p; ++p)
  {
    ++len;
  }

  char *left = clean;
  char *right = clean + (len - 1);
  while (left < right)
  {
    char tmp = *left;
    *left++ = *right;
    *right-- = tmp;
  }

  int index = 0;
  for (int chunk = 1; index < len; ++chunk)
  {
    int remain = len - index;
    int take = (chunk < remain ? chunk : remain);
    for (int k = 0; k < take; ++k)
    {
      cout << clean[index + k];
    }
    cout << '\n';
    index += take;
  }

  delete[] clean;
  return 0;
}
