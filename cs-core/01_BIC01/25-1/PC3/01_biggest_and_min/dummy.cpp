#include <iostream>

using std::cin;
using std::cout;
using std::endl;

// Withouth using any structure :/
// As expected in this introductory course

int main()
{
  int one;
  int two;
  int three;

  cout << "Ingresa el numero 1: ";
  cin >> one;

  cout << "Ingresa el numero 2: ";
  cin >> two;

  cout << "Ingresa el numero 3: ";
  cin >> three;

  int maxNumber;
  int minNumber;

  // Finding the maximum

  if (one > two && one > three)
  {
    maxNumber = one;
  }

  if (two > one && two > three)
  {
    maxNumber = two;
  }

  if (three > one && three > two)
  {
    maxNumber = three;
  }

  // finding the minimum
  if (one < two && one < three)
  {
    minNumber = one;
  }

  if (two < one && two < three)
  {
    minNumber = two;
  }

  if (three < one && three < two)
  {
    minNumber = three;
  }

  cout << endl;

  cout << "El numero maximo es: " << maxNumber << endl;
  cout << "El numero minimo es: " << minNumber << endl;

  cout << endl
       << "We found the maximum and minum using the dummy mode!"
       << endl;

  return 0;
}