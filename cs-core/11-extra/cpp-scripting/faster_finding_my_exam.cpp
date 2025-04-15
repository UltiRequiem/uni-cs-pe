#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>
#include "httplib.h"

std::mutex cout_mutex;
std::atomic<int> progress_counter(0);
const int NUM_THREADS = 16;

void check_range(int start, int end)
{
  httplib::Client cli("univirtual.uni.pe");
  cli.set_follow_location(true);

  for (int i = start; i <= end; ++i)
  {
    int current = ++progress_counter;
    if (current % 1000 == 0)
    {
      std::lock_guard<std::mutex> lock(cout_mutex);
      std::cout << "Progress: " << current << " / 900000 ("
                << std::fixed << std::setprecision(2)
                << (current * 100.0 / 900000) << "%)" << std::endl;
    }

    std::stringstream path;
    path << "/pluginfile.php/" << std::setfill('0') << std::setw(6) << i
         << "/mod_resource/content/1/PC1_CC112.pdf";

    auto res = cli.Head(path.str().c_str());

    if (res && res->status < 400)
    {
      std::lock_guard<std::mutex> lock(cout_mutex);
      std::cout << "✅ Found for " << i << ": " << path.str() << std::endl;
    }
  }
}

int main()
{
  std::vector<std::thread> threads;

  int range_size = (999999 - 100000 + 1) / NUM_THREADS;

  for (int t = 0; t < NUM_THREADS; ++t)
  {
    int start = 100000 + t * range_size;
    int end = (t == NUM_THREADS - 1) ? 999999 : start + range_size - 1;

    threads.push_back(std::thread(check_range, start, end));
  }

  for (auto &thread : threads)
  {
    thread.join();
  }

  std::cout << "All checks completed!" << std::endl;
  return 0;
}