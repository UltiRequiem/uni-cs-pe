#include <chrono>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <vector>

#include "sieva.hpp"

namespace
{

  std::size_t count_primes(const std::vector<bool> &sieve)
  {
    std::size_t count = 0;
    for (const bool is_prime : sieve)
    {
      if (is_prime)
      {
        ++count;
      }
    }
    return count;
  }

} // namespace

int main()
{
  using clock = std::chrono::steady_clock;
  using ms = std::chrono::duration<double, std::milli>;

  const std::vector<std::size_t> inputs{10'000, 100'000, 1'000'000, 5'000'000};

  std::cout << "Benchmarking sieva(target)\n";
  std::cout << "target, primes_found, elapsed_ms\n";

  for (const std::size_t target : inputs)
  {
    const auto start = clock::now();
    const auto sieve = sieva(target);
    const auto end = clock::now();

    const auto elapsed = std::chrono::duration_cast<ms>(end - start).count();
    const auto prime_count = count_primes(sieve);

    std::cout << target << ", " << prime_count << ", " << std::fixed
              << std::setprecision(3) << elapsed << "\n";
  }

  return 0;
}
