#include <iostream>

int min(int a, int b)
{
  return (a < b) ? a : b;
}

int minDaysToEat(int n)
{
  if (n <= 0)
  {
    return 0;
  }

  int result = 1 + minDaysToEat(n - 1);

  if (n % 2 == 0)
  {
    result = min(result, 1 + minDaysToEat(n / 2));
  }

  if (n % 3 == 0)
  {
    result = min(result, 1 + minDaysToEat(n / 3));
  }

  return result;
}

int main()
{

  int n;
  std::cout << "Enter the number of apples: ";
  std::cin >> n;

  std::cout << "Minimum days needed: " << minDaysToEat(n) << std::endl;

  std::cout << "For n = 6: " << minDaysToEat(6) << " days" << std::endl;
  std::cout << "For n = 10: " << minDaysToEat(10) << " days" << std::endl;

  return 0;
}