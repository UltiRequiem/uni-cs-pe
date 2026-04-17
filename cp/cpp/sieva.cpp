#include "sieva.hpp"

using std::vector;

vector<bool> sieva(const std::size_t target)
{
  std::vector<bool> primes(target, true);

  if (target > 0)
  {
    primes[0] = false;
  }
  if (target > 1)
  {
    primes[1] = false;
  }

  for (std::size_t i = 4; i < target; i += 2)
  {
    primes[i] = false;
  }

  for (std::size_t i = 3; i * i < target; i += 2)
  {
    if (!primes[i])
    {
      continue;
    }

    for (std::size_t j = i * i; j < target; j += i * 2)
    {
      primes[j] = false;
    }
  }

  return primes;
}
