#include <iostream>
#include <filesystem>
#include <string>
#include <locale>
#include <codecvt>

using namespace std;
namespace fs = std::filesystem;

string to_lowercase(const string &str)
{
  string result = str;

  for (char &c : result)
  {
    c = tolower(c);
  }

  return result;
}

string remove_accents(const std::string &str)
{
  string result = str;

  string accents = "áéíóúüÁÉÍÓÚÜ";
  string replacements = "aeioouAEIOOU";

  for (size_t i = 0; i < str.length(); i++)
  {
    for (size_t j = 0; j < accents.length(); j++)
    {
      if (str[i] == accents[j])
      {
        result[i] = replacements[j];
        break;
      }
    }
  }

  return result;
}

string to_snake_case(const string &filename)
{
  size_t dot_pos = filename.find_last_of('.');
  string name = filename.substr(0, dot_pos);
  string ext = (dot_pos != string::npos) ? filename.substr(dot_pos) : "";
  name = to_lowercase(name);

  name = remove_accents(name);

  string result;
  bool prev_is_space = false;

  for (char c : name)
  {
    if (isalnum(c))
    {
      result += c;
      prev_is_space = false;
    }
    else if (!prev_is_space)
    {
      result += '_';
      prev_is_space = true;
    }
  }

  while (!result.empty() && result.back() == '_')
  {
    result.pop_back();
  }

  return result + ext;
}

int main()
{
  std::string base_path = "sciences/physics-01";

  try
  {
    for (const auto &entry : fs::directory_iterator(base_path))
    {
      if (fs::is_regular_file(entry.path()))
      {
        string old_filename = entry.path().filename().string();
        string new_filename = to_snake_case(old_filename);

        fs::path new_path = entry.path().parent_path() / new_filename;

        cout << "Renaming: " << old_filename << " -> " << new_filename << std::endl;
        fs::rename(entry.path(), new_path);
      }
    }

    std::cout << "File renaming completed successfully!" << std::endl;
  }
  catch (const std::exception &e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}