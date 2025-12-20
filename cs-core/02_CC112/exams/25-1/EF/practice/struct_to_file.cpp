#include <iostream>
#include <fstream>
#include <string>

using std::cout;
using std::endl;
using std::ifstream;
using std::ios;
using std::ofstream;
using std::string;

struct Person
{
  int id;
  std::string name;
  double salary;
  int age;

  Person() : id(0), name(""), salary(0.0), age(0) {}

  Person(int _id, const string &_name, double _salary, int _age)
      : id(_id), name(_name), salary(_salary), age(_age) {}

  void display() const
  {
    cout << "ID: " << id << ", Name: " << name
         << ", Salary: " << salary << ", Age: " << age << endl;
  }

  void writeToBinary(ofstream &outFile) const
  {
    outFile.write(reinterpret_cast<const char *>(&id), sizeof(id));
    outFile.write(reinterpret_cast<const char *>(&salary), sizeof(salary));
    outFile.write(reinterpret_cast<const char *>(&age), sizeof(age));

    size_t nameLength = name.length();

    outFile.write(reinterpret_cast<const char *>(&nameLength), sizeof(nameLength));
    outFile.write(name.c_str(), nameLength);
  }

  void readFromBinary(ifstream &inFile)
  {
    inFile.read(reinterpret_cast<char *>(&id), sizeof(id));
    inFile.read(reinterpret_cast<char *>(&salary), sizeof(salary));
    inFile.read(reinterpret_cast<char *>(&age), sizeof(age));

    size_t nameLength;
    inFile.read(reinterpret_cast<char *>(&nameLength), sizeof(nameLength));

    name.resize(nameLength);
    inFile.read(&name[0], nameLength);
  }
};

void writePersonToBinaryFile(const Person &person, const string &filename)
{
  ofstream outFile(filename, ios::binary);

  if (outFile.is_open())
  {
    person.writeToBinary(outFile);
    outFile.close();
    cout << "Person written to binary file successfully!" << endl;
    return;
  }

  std::cout << "Error: Could not open file for writing!" << endl;
}

Person readPersonFromBinaryFile(const string &filename)
{
  Person person;
  ifstream inFile(filename, ios::binary);

  if (inFile.is_open())
  {
    person.readFromBinary(inFile);
    inFile.close();
    std::cout << "Person read from binary file successfully!" << endl;
  }
  else
  {
    std::cout << "Error: Could not open file for reading!" << std::endl;
  }

  return person;
}

void writePersonToTextFile(const Person &person, const string &filename)
{
  ofstream outFile(filename);

  if (outFile.is_open())
  {
    outFile << person.id << std::endl;
    outFile << person.name << std::endl;
    outFile << person.salary << std::endl;
    outFile << person.age << std::endl;
    outFile.close();
    cout << "Person written to text file successfully!" << endl;
  }
  else
  {
    cout << "Error: Could not open file for writing!" << endl;
  }
}

Person readPersonFromTextFile(const string &filename)
{
  Person person;
  std::ifstream inFile(filename);

  if (inFile.is_open())
  {
    inFile >> person.id;
    inFile.ignore();
    getline(inFile, person.name);
    inFile >> person.salary >> person.age;
    inFile.close();
    cout << "Person read from text file successfully!" << std::endl;
  }
  else
  {
    std::cout << "Error: Could not open file for reading!" << std::endl;
  }

  return person;
}

int main()
{
  Person person1(1, "John Doe Smith", 50000.50, 30);
  cout << "Original person: ";
  person1.display();

  cout << "\n=== BINARY FILE OPERATIONS ===" << endl;

  writePersonToBinaryFile(person1, "person.bin");
  Person readPersonBinary = readPersonFromBinaryFile("person.bin");
  cout << "Read from binary: ";
  readPersonBinary.display();

  cout << "\n=== TEXT FILE OPERATIONS ===" << endl;

  writePersonToTextFile(person1, "person.txt");
  Person readPersonText = readPersonFromTextFile("person.txt");
  cout << "Read from text: ";
  readPersonText.display();

  return 0;
}