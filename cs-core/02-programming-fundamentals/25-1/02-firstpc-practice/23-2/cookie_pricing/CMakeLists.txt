cmake_minimum_required(VERSION 3.10)
project(CookiePricing)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_library(cookie_pricing src/cookie_pricing.cpp)
add_executable(cookie_pricing_test tests/cookie_pricing_test.cpp)
target_link_libraries(cookie_pricing_test
  PRIVATE
    cookie_pricing
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(cookie_pricing_test)