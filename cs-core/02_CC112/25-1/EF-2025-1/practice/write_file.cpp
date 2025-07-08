#include <iostream>
#include <fstream>
#include <string>

using std::cerr;
using std::endl;
using std::ofstream;

int main()
{

  ofstream outfile("data.txt");

  if (!outfile.is_open())
  {
    cerr << "Error opening file for writing." << endl;
    return 1;
  }

  outfile << "Hello, World!" << endl;
  outfile << "Goodbye!" << endl;

  outfile.close();

  return 0;
}