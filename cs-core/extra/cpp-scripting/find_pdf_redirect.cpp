#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "httplib.h"

std::string make_url(int number)
{
  std::ostringstream oss;
  oss << "https://univirtual.uni.pe/pluginfile.php/"
      << std::setfill('0') << std::setw(6) << number
      << "/mod_resource/content/1/PC1_CC112.pdf";
  return oss.str();
}

int main()
{
  httplib::Client cli("univirtual.uni.pe");
  cli.set_follow_location(true);

  for (int i = 100000; i <= 999999; ++i)
  {
    if (i % 1000 == 0)
    {
      std::cout << "Progress: " << i << " / 999999" << std::endl;
    }

    std::stringstream path;
    path << "/pluginfile.php/" << std::setfill('0') << std::setw(6) << i << "/mod_resource/content/1/PC1_CC112.pdf";

    auto res = cli.Head(path.str().c_str());

    if (res && res->status < 400)
    {
      std::cout << "✅ Found for " << i << ": " << path.str() << std::endl;
    }
  }

  return 0;
}