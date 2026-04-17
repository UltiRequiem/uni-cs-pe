#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "sieva.hpp"

namespace
{

  void expect_true(const bool condition, const std::string &message)
  {
    if (!condition)
    {
      throw std::runtime_error(message);
    }
  }

  void test_handles_small_targets()
  {
    expect_true(sieva(0).empty(), "sieva(0) should be empty");
    expect_true(sieva(1) == std::vector<bool>{false}, "sieva(1) mismatch");
    expect_true(sieva(2) == std::vector<bool>{false, false}, "sieva(2) mismatch");
  }

  void test_marks_primes_below_10()
  {
    const std::vector<bool> expected{
        false,
        false,
        true,
        true,
        false,
        true,
        false,
        true,
        false,
        false,
    };

    expect_true(sieva(10) == expected, "sieva(10) mismatch");
  }

  void test_marks_composites_for_larger_range()
  {
    const auto primes = sieva(20);

    expect_true(primes[11], "11 should be prime");
    expect_true(!primes[12], "12 should be composite");
    expect_true(primes[17], "17 should be prime");
    expect_true(!primes[18], "18 should be composite");
  }

} // namespace

int main()
{
  int failures = 0;

  const auto run = [&failures](const char *name, const auto &test_fn)
  {
    try
    {
      test_fn();
      std::cout << "[PASS] " << name << '\n';
    }
    catch (const std::exception &ex)
    {
      ++failures;
      std::cerr << "[FAIL] " << name << ": " << ex.what() << '\n';
    }
  };

  run("handles small targets", test_handles_small_targets);
  run("marks primes below 10", test_marks_primes_below_10);
  run("marks composites correctly for larger range", test_marks_composites_for_larger_range);

  if (failures == 0)
  {
    std::cout << "All tests passed\n";
    return EXIT_SUCCESS;
  }

  std::cerr << failures << " test(s) failed\n";
  return EXIT_FAILURE;
}
