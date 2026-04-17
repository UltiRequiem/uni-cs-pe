#include <catch2/catch_test_macros.hpp>

#include "sieva.hpp"

TEST_CASE("handles small targets", "[sieva]") {
  REQUIRE(sieva(0).empty());
  REQUIRE(sieva(1) == std::vector<bool>{false});
  REQUIRE(sieva(2) == std::vector<bool>{false, false});
}

TEST_CASE("marks primes below 10", "[sieva]") {
  const std::vector<bool> expected{
      false, false, true, true, false, true, false, true, false, false,
  };

  REQUIRE(sieva(10) == expected);
}

TEST_CASE("marks composites correctly for larger range", "[sieva]") {
  const auto primes = sieva(20);

  REQUIRE(primes[11]);
  REQUIRE_FALSE(primes[12]);
  REQUIRE(primes[17]);
  REQUIRE_FALSE(primes[18]);
}
