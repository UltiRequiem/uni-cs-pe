#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int readInt()
{
  int value;
  cin >> value;

  if (value <= 0)
  {
    throw std::invalid_argument("Value must be greater than 0.");
  }

  return value;
}

int main()
{
  try
  {
    int size = readInt();

    int *array = new int[size];

    for (int i = 0; i < size; ++i)
    {
      array[i] = i * 2;
    }

    for (int i = 0; i < size; ++i)
    {
      cout << "Element " << i << ": " << array[i] << endl;
    }

    delete[] array;

    return 0;
  }
  catch (const std::invalid_argument &e)
  {
    std::cerr << "Invalid input: " << e.what() << std::endl;
  }
  catch (const std::exception &e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  return 1;
}