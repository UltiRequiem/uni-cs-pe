#include <iostream>
#include <fstream>
#include <string>

using std::cerr;
using std::cout;
using std::endl;
using std::string;

using std::ifstream;

int main()
{
  ifstream file("data.txt");

  if (!file.is_open())
  {
    cerr << "Could not open the file" << endl;
    return 1;
  }

  string text;

  // line by line
  while (file >> text)
  {
    cout << text << endl;
  }

  file.close();
}