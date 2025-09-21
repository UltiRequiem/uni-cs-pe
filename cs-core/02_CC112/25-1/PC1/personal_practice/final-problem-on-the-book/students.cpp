#include<string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct Student {
  string name;
  int age;

  float grade;

  void display() const {
    cout << "Name: " << name << ", Age: " << age << ", Grade: " << grade << endl;
  }
};

const string PATH = "/home/eliaz/Documents/uni/programming-fundaments/final-problem-on-the-book/students.csv";

int main() {
  ifstream inputFile;
  inputFile.open(PATH);

  if (!inputFile.is_open()) {
    cerr << "Problems reading the file" << endl;
    return 1;
  }

  string line = "";
  vector < Student > students;

  while (getline(inputFile, line)) {
    stringstream currentLine(line);
    string name, age_str, grade_str;

    getline(currentLine, name, ',');
    getline(currentLine, age_str, ',');
    getline(currentLine, grade_str);

    line = "";

    try {
      auto student = Student {
        name,
        stoi(age_str),
        stof(grade_str)
      };
      students.push_back(student);
    } catch (exception & e) {
      cerr << "Error parsing line: " << line << endl;
      return 1;
    }
  }

  for (const auto & student: students) {
    student.display();
  }

  return 0;
}