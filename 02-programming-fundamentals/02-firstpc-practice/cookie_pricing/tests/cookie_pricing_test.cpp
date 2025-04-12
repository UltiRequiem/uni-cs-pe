#include <gtest/gtest.h>
#include "../src/cookie_pricing.h"

class CookiePricingTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Common test array used in the example
        baseArray[0] = 8.8;
        baseArray[1] = 10.1;
        baseArray[2] = 14.4;
        baseArray[3] = 16.6;
        baseArray[4] = 18.8;
        baseArray[5] = 20.5;
        baseSize = 6;
    }

    double baseArray[6];
    int baseSize;
};

// Test 1: Original example case
TEST_F(CookiePricingTest, OriginalExample) {
    double result = calculateSuggestedPrice(11.0, baseArray, baseSize);
    EXPECT_NEAR(result, 0.6125, 0.0001);
}

// Test 2: Weight less than minimum
TEST_F(CookiePricingTest, WeightBelowMinimum) {
    double result = calculateSuggestedPrice(5.0, baseArray, baseSize);
    EXPECT_NEAR(result, 0.44, 0.0001);  // 8.8/20
}

// Test 3: Weight more than maximum
TEST_F(CookiePricingTest, WeightAboveMaximum) {
    double result = calculateSuggestedPrice(25.0, baseArray, baseSize);
    EXPECT_NEAR(result, 1.025, 0.0001);  // 20.5/20
}

// Test 4: Exact match to an array value
TEST_F(CookiePricingTest, ExactMatch) {
    double result = calculateSuggestedPrice(14.4, baseArray, baseSize);
    EXPECT_NEAR(result, 0.72, 0.0001);  // 14.4/20
}

// Test 5: Weight between two values
TEST_F(CookiePricingTest, BetweenValues) {
    double result = calculateSuggestedPrice(15.5, baseArray, baseSize);
    EXPECT_NEAR(result, 0.775, 0.0001);  // ((14.4 + 16.6)/2)/20
}

// Test 6: Weight at 20g (reference point)
TEST_F(CookiePricingTest, ReferencePoint) {
    double result = calculateSuggestedPrice(20.0, baseArray, baseSize);
    EXPECT_NEAR(result, 1.0, 0.0001);
}

// Test 7: Small array
TEST_F(CookiePricingTest, SmallArray) {
    double smallArray[] = {5.0, 10.0};
    double result = calculateSuggestedPrice(7.5, smallArray, 2);
    EXPECT_NEAR(result, 0.375, 0.0001);  // 7.5/20
}

// Test 8: Equal consecutive values
TEST_F(CookiePricingTest, EqualValues) {
    double equalArray[] = {10.0, 10.0, 15.0};
    double result = calculateSuggestedPrice(10.0, equalArray, 3);
    EXPECT_NEAR(result, 0.5, 0.0001);  // 10/20
}

// Test 9: Very close values
TEST_F(CookiePricingTest, CloseValues) {
    double closeArray[] = {10.0, 10.1, 10.2};
    double result = calculateSuggestedPrice(10.15, closeArray, 3);
    EXPECT_NEAR(result, 0.5075, 0.0001);  // ((10.1 + 10.2)/2)/20
}

// Test 10: Single element array
TEST_F(CookiePricingTest, SingleElement) {
    double singleArray[] = {15.0};
    double result = calculateSuggestedPrice(10.0, singleArray, 1);
    EXPECT_NEAR(result, 0.75, 0.0001);  // 15/20
}