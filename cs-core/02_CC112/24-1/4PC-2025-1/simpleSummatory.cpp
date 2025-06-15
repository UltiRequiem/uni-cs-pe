// This CLI program reads two files and writes the
// sum of each line in a third file.

#include <fstream>
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::ofstream;
using std::stoi;
using std::string;

void writeResults(ifstream &input1, ifstream &input2, ofstream &output) {
  int firstFileLines = 0;
  int *firstFileNumbers = nullptr;
  string line1;

  while (getline(input1, line1)) {
    int number = stoi(line1);

    int *newNumbers = new int[firstFileLines + 1];

    for (int i = 0; i < firstFileLines; i++) {
      newNumbers[i] = firstFileNumbers[i];
    }

    newNumbers[firstFileLines] = number;
    firstFileLines++;

    delete[] firstFileNumbers;
    firstFileNumbers = newNumbers;
  }

  int secondFileLines = 0;
  int *secondFileNumbers = nullptr;
  string line2;

  while (getline(input2, line2)) {
    int number = stoi(line2);

    int *newNumbers = new int[secondFileLines + 1];

    for (int i = 0; i < secondFileLines; i++) {
      newNumbers[i] = secondFileNumbers[i];
    }

    newNumbers[secondFileLines] = number;
    secondFileLines++;

    delete[] secondFileNumbers;
    secondFileNumbers = newNumbers;
  }

  if (firstFileLines != secondFileLines) {
    cerr << "Error: The files do not have the same number of lines." << endl;
    delete[] firstFileNumbers;
    delete[] secondFileNumbers;
    return;
  }

  for (int i = 0; i < firstFileLines; i++) {
    int sum = firstFileNumbers[i] + secondFileNumbers[i];
    cout << "Sum of line " << (i + 1) << ": " << sum << endl;
    output << sum << endl;
  }

  delete[] firstFileNumbers;
  delete[] secondFileNumbers;
}
